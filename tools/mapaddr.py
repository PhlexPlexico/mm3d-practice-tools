"""Map and verify USA 1.0 game addresses against USA 1.1.

USA 1.1 is a recompile, not a relocation -- there are 43 distinct deltas across the
binary, register allocation differs, and some function bodies genuinely changed. So a
1.1 address cannot be computed from a 1.0 one; it has to be found and verified.

That search is mechanical, though, and this does it: locate the 1.0 code at a given
address inside the 1.1 image by matching its instruction bytes, ignoring the things that
legitimately move between builds (PC-relative branch immediates, and literal-pool words
holding image addresses). A match only counts if it is unique.

    python3 tools/mapaddr.py 0x1EB58C 0x233BEC     resolve addresses, print the result
    python3 tools/mapaddr.py --add NAME 0x1EB58C   resolve and append to addresses.tsv
    python3 tools/mapaddr.py --check               re-verify every row in addresses.tsv

--check is the important one: wire it into the build so a stale or wrong 1.1 address is a
build failure rather than a wild branch discovered months later. Exits non-zero on any
failure.

Both game images are needed. By default they are looked for next to the repo root as
code1.0.bin and code.bin; override with MM3D_CODE_10 / MM3D_CODE_11.
"""
import os
import struct
import sys

TSV = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'addresses.tsv')
_HERE = os.path.dirname(os.path.abspath(__file__))
CODE_10 = os.environ.get('MM3D_CODE_10', os.path.join(_HERE, '..', 'bin', 'code1.0.bin'))
CODE_11 = os.environ.get('MM3D_CODE_11', os.path.join(_HERE, '..', 'bin', 'code1.1.bin'))

BASE = 0x100000
# Region layout from the USA 1.1 exheader. Verification differs per region: .text can be
# compared as code, .rodata/.data hold pointers that relocate, and .bss has no file
# content at all so its addresses can only be trusted, never checked.
TEXT_END = 0x61D000
DATA_END = 0x6B1000
BSS_END = 0x7CF000
# window sizes tried in order: (bytes, bytes-before-the-address). Forward-only windows
# suit function entries, where the bytes before belong to the previous function and
# relocate independently; centred windows suit mid-function patch sites.
WINDOWS = ((64, 0), (96, 0), (128, 0), (192, 0), (64, 32), (128, 64), (256, 128))
MIN_ANCHOR = 8          # shortest exact byte run worth searching on
MAX_HITS = 3            # more than this and we call it ambiguous rather than guess

# Symbols whose 1.1 content legitimately differs from 1.0, confirmed by hand. --check
# cannot verify these by byte comparison, so they are excused with the reasoning recorded.
MANUAL = {
    # 1.1 recompiled this function with different register allocation: the patch site is
    # `mov r9,r0` in 1.0 and `mov r10,r0` in 1.1. Confirmed by matching the surrounding
    # instruction sequence (mov/bl/mov/mov/bl), which is identical apart from registers.
    # NOTE: hook_EnteringLocation writes r9 and must write r10 on 1.1.
    'EnteringLocation',
}


def load():
    try:
        a = open(CODE_10, 'rb').read()
        b = open(CODE_11, 'rb').read()
    except IOError as e:
        sys.exit('cannot read game images (%s).\n'
                 '  expected %s and %s\n'
                 '  override with MM3D_CODE_10 / MM3D_CODE_11' % (e, CODE_10, CODE_11))
    return a, b


V10, V11 = load()
LO, HI = BASE, BASE + len(V10)


def mask(buf, soft=False):
    """Blank the bits that legitimately differ between two builds of the same code.

    Always: PC-relative B/BL immediates, which change whenever code moves.
    With soft=True: words holding an image address, i.e. literal-pool entries pointing at
    globals that relocate without the surrounding code changing.
    """
    out = bytearray(buf)
    for k in range(0, len(out) - 3, 4):
        w = struct.unpack('<I', out[k:k + 4])[0]
        if (w & 0x0E000000) == 0x0A000000:
            struct.pack_into('<I', out, k, w & 0xFF000000)
        elif soft and BASE <= w < BSS_END:
            struct.pack_into('<I', out, k, 0)
    return bytes(out)


def region(addr):
    if addr < TEXT_END:
        return 'text'
    if addr < DATA_END:
        return 'data'
    if addr < BSS_END:
        return 'bss'
    return 'beyond'


def _anchor(off, size):
    """Longest run of words that neither branch nor hold an address, to search on."""
    best, cur = (0, 0), 0
    for k in range(0, size, 4):
        w = struct.unpack('<I', V10[off + k:off + k + 4])[0]
        if (w & 0x0E000000) == 0x0A000000 or LO <= w < HI:
            cur = 0
        else:
            cur += 4
            if cur > best[0]:
                best = (cur, k + 4 - cur)
    return best


def _try(addr, size, back, soft):
    off = addr - BASE - back
    if off < 0 or off + size > len(V10):
        return None
    alen, aoff = _anchor(off, size)
    if alen < MIN_ANCHOR:
        return None
    pattern = mask(V10[off:off + size], soft)
    key = V10[off + aoff:off + aoff + alen]
    hits, at = [], 0
    while True:
        p = V11.find(key, at)
        if p < 0:
            break
        x = p - aoff
        if 0 <= x <= len(V11) - size and mask(V11[x:x + size], soft) == pattern:
            hits.append(x + BASE + back)
        at = p + 1
        if len(hits) > MAX_HITS:
            return None
    return hits[0] if len(hits) == 1 else None


def resolve(addr):
    """Unique 1.1 address for a 1.0 address, plus how it was found. (None, reason) if not."""
    if not (LO <= addr < HI):
        return None, 'outside the game image'
    for size, back in WINDOWS:
        for soft in (False, True):
            hit = _try(addr, size, back, soft)
            if hit is not None:
                return hit, 'window %d/%d%s' % (size, back, ' soft' if soft else '')
    return None, 'no unique match'


DATA_START = 0x64B000
# Unanimity, not a quorum. Some globals are referenced from only one or two
# places, and demanding three votes rejected addresses that were provably right
# (0x6F4130 -> 0x6F4138 has exactly two references and is confirmed correct).
# A single dissenting vote is what should stop us, not a small sample.


def _count_refs(img, addr):
    """How many word-aligned places in this image hold this address."""
    needle = struct.pack('<I', addr)
    n, at = 0, 0
    while True:
        p = img.find(needle, at)
        if p < 0:
            return n
        at = p + 4
        if p % 4 == 0:
            n += 1


def _no_refs_anywhere(a10, a11):
    """True when neither address is named by a literal in either image.

    Some globals are only ever reached as an offset from a base pointer, so
    there is no literal to count and reference checking can say nothing about
    them either way. That is different from the references disagreeing.
    """
    return (_count_refs(V10, a10) == 0 and _count_refs(V11, a10) == 0
            and _count_refs(V11, a11) == 0)


def _refcounts_agree(target, candidate, tolerance=2):
    """Did the references to `target` in 1.0 move wholesale to `candidate` in 1.1?

    A global that relocated leaves nothing behind: every literal that pointed at
    the old address points at the new one instead. So the old address should
    have roughly N references in 1.0 and none in 1.1, and the new address the
    reverse. That is a far stronger signal than the vote, and it is independent
    of whether any surrounding code could be matched.

    Small differences are allowed -- a call site can legitimately appear or
    disappear between builds.
    """
    if target == candidate:
        return _count_refs(V10, target) > 0 and _count_refs(V11, target) > 0
    old10, old11 = _count_refs(V10, target), _count_refs(V11, target)
    new10, new11 = _count_refs(V10, candidate), _count_refs(V11, candidate)
    return (old10 > 0 and old11 == 0 and new10 == 0
            and abs(new11 - old10) <= tolerance)


def resolve_data(target, max_refs=24):
    """1.1 address for a .data/.bss address, by following references to it.

    Content matching cannot reach past the end of the image, and .bss simply is
    not in the file, so resolve() is useless here. What does work: find the
    literal-pool words in 1.0 that hold this address, map each of those *code
    sites* into 1.1 with the ordinary resolver, and read back whichever address
    1.1 stores there. Several independent references voting for the same answer
    is the evidence.

    Measured on this pair, .data and .bss are very nearly identity-mapped: of
    the addresses referenced by this project, all but a couple sit at the same
    place in both builds. So agreeing with `target` is the expected result and
    is accepted quietly; anything else is real news and is reported as needing a
    human to confirm it against Ghidra before it goes in the table.

    Returns (addr, why, needs_review).
    """
    if target < DATA_END:
        hit, why = resolve(target)
        if hit is not None:
            return hit, why, hit != target

    needle = struct.pack('<I', target)
    votes = {}
    checked = 0
    at = 0
    while checked < max_refs:
        p = V10.find(needle, at)
        if p < 0:
            break
        at = p + 4
        if p % 4:
            continue                       # not a word-aligned literal
        lit = p + BASE
        if lit >= TEXT_END:
            # A pointer living in .data relocates with its own section, and
            # .data is identity-mapped, so read the same offset in 1.1.
            if p + 4 <= len(V11):
                got = struct.unpack('<I', V11[p:p + 4])[0]
                votes[got] = votes.get(got, 0) + 1
                checked += 1
            continue
        hit, _ = resolve(lit)
        checked += 1
        if hit is None:
            continue
        off = hit - BASE
        if off + 4 <= len(V11):
            got = struct.unpack('<I', V11[off:off + 4])[0]
            votes[got] = votes.get(got, 0) + 1

    if not votes:
        return None, 'no usable references found', False
    best, count = max(votes.items(), key=lambda kv: kv[1])
    total = sum(votes.values())
    corroborated = _refcounts_agree(target, best)
    # Unanimous is enough however few references there are -- some globals are
    # touched from only one or two places. Otherwise demand both a clear
    # majority and enough votes for one bad resolve not to swing it.
    ok = (count == total) or (count >= 3 and count >= 0.8 * total)
    if not ok:
        return None, 'references disagree (%s)' % ', '.join(
            '0x%06X x%d' % (k, v) for k, v in sorted(votes.items(), key=lambda kv: -kv[1])), False
    why = 'xref %d/%d%s' % (count, total, ' +refcount' if corroborated else '')
    # A moved global takes all its references with it, so the counts swapping
    # cleanly is much stronger evidence than the vote alone. When it holds there
    # is nothing left for a human to check, even if the address did move.
    return best, why, (best != target) and not corroborated


def verify(a10, a11, size=64):
    """Does the 1.0 content at a10 still match the 1.1 content at a11?

    Returns (state, detail) where state is 'ok', 'skip' or 'fail'. 'skip' means the
    address cannot be checked from file content -- .bss is zero-filled at load and simply
    is not in the image -- so the mapping is trusted rather than verified.
    """
    reg = region(a10)
    if reg in ('bss', 'beyond'):
        # There is no file content at a .bss address, so the original tool gave
        # up here and trusted the row. That is exactly how a wrong address
        # survives: mm3dr's table still carries 0x6B7B8C for a global that USA
        # 1.1 moved to 0x6B7B94, because nothing ever checked it.
        #
        # References can be checked, though. If the global really is at a11 in
        # 1.1, every literal that pointed at a10 now points at a11 and none are
        # left behind.
        if _no_refs_anywhere(a10, a11):
            return 'skip', 'in .bss and never named by a literal'
        if _refcounts_agree(a10, a11):
            return 'ok', 'references moved with it'
        return 'fail', ('%d refs to 0x%06X in 1.0 / %d in 1.1; %d refs to 0x%06X in 1.1'
                        % (_count_refs(V10, a10), a10, _count_refs(V11, a10),
                           _count_refs(V11, a11), a11))
    if reg == 'data':
        # A 64-byte window in .data spills into neighbouring variables, and adjacent data
        # can differ for reasons that say nothing about this address -- Nintendo's build
        # path string, for one, which reads ...\joker\ in 1.0 and ...\joker-1_1_0\ in 1.1.
        size = 32
    o, x = a10 - BASE, a11 - BASE
    if o < 0 or x < 0 or o + size > len(V10) or x + size > len(V11):
        return 'skip', 'window runs past end of image'
    a, b = V10[o:o + size], V11[x:x + size]
    if reg == 'data' and a.count(b'\x00') == len(a) and b.count(b'\x00') == len(b):
        # A pointer the game fills in at runtime: zero on disk in both builds,
        # so there is no content to compare. Its references still tell us
        # whether it moved.
        if _no_refs_anywhere(a10, a11):
            # Reached as an offset from some base pointer, so no literal names
            # it. Content matching is the only evidence available, and it is
            # what put the row in the table.
            return 'skip', 'zero-filled and never named by a literal'
        if _refcounts_agree(a10, a11):
            return 'ok', 'zero-filled; references moved with it'
        return 'fail', 'zero-filled and references do not line up'
    if mask(a) == mask(b):
        return 'ok', 'exact'
    if mask(a, True) == mask(b, True):
        return 'ok', 'relocated refs'
    words = sum(1 for i in range(0, size - 3, 4) if a[i:i + 4] != b[i:i + 4])
    return 'fail', '%s, %d/%d words differ' % (reg, words, size // 4)


def _regs(word):
    """Register operand fields of an ARM instruction: Rn, Rd, Rs, Rm."""
    return ((word >> 16) & 0xF, (word >> 12) & 0xF, (word >> 8) & 0xF, word & 0xF)


def _same_shape(a, b):
    """Same instruction ignoring its register operands."""
    m = ~0x000FFF0F & 0xFFFFFFFF
    return (a & m) == (b & m)


def regcheck(a10, a11, before=16, after=16):
    """Instructions around a patch site whose registers were reallocated in 1.1.

    A hook is written against the registers the surrounding code happens to use. Those
    are not part of the address, so an address can map perfectly while the contract
    underneath it changes -- 1.1 recompiled EnteringLocation to use r10 where 1.0 used r9.
    Nothing else in the build catches that, so surface it here.
    """
    if region(a10) != 'text':
        return []
    o, x = a10 - BASE - before, a11 - BASE - before
    n = before + after
    if o < 0 or x < 0 or o + n > len(V10) or x + n > len(V11):
        return []
    out = []
    for k in range(0, n, 4):
        w10 = struct.unpack('<I', V10[o + k:o + k + 4])[0]
        w11 = struct.unpack('<I', V11[x + k:x + k + 4])[0]
        if w10 == w11:
            continue
        if (w10 & 0x0E000000) == 0x0A000000 and (w11 & 0x0E000000) == 0x0A000000:
            continue                                  # branch immediates always differ
        if BASE <= w10 < BSS_END or BASE <= w11 < BSS_END:
            continue                                  # literal pool: a relocated pointer,
            # not an instruction. Two nearby pointers can differ only in the low bits and
            # look exactly like a register-field change.
        if _same_shape(w10, w11):
            r10, r11 = _regs(w10), _regs(w11)
            moved = [(nm, x0, x1) for nm, x0, x1
                     in zip(('Rn', 'Rd', 'Rs', 'Rm'), r10, r11) if x0 != x1]
            if moved:
                out.append((a10 - before + k, w10, w11, moved))
    return out


def check_loader_base(a10, a11):
    """The loader lives in the padding after the text segment, so both addresses
    must sit at the very start of a run of zeros that reaches the segment end.

    Worth checking separately: this row is the one place where being a few bytes
    wrong means overwriting live game code rather than failing to link. Content
    matching happens to find it, but padding is exactly the kind of region where
    a match is luck rather than evidence.
    """
    problems = []
    for img, addr, label in ((V10, a10, '1.0'), (V11, a11, '1.1')):
        off = addr - BASE
        end = TEXT_END - BASE
        if not (0 <= off < end):
            problems.append('%s: 0x%06X is outside the text segment' % (label, addr))
            continue
        if any(img[off:end]):
            problems.append('%s: 0x%06X is not all zeros up to the segment end' % (label, addr))
        if off > 0 and img[off - 1] == 0:
            problems.append('%s: 0x%06X is not the first free byte -- padding starts earlier'
                            % (label, addr))
        free = end - off
        if free < 72:
            problems.append('%s: only %d bytes free at 0x%06X' % (label, free, addr))
    return problems


def rows():
    for line in open(TSV):
        line = line.rstrip('\n')
        if not line.strip() or line.startswith('#'):
            continue
        parts = line.split('\t')
        if len(parts) >= 3:
            yield parts[0], parts[1], parts[2]


def cmd_check():
    ok = failed = unmapped = skipped = excused = 0
    problems = []
    for row in rows():
        name, a10, a11 = row[0], row[1], row[2]
        if a11.strip() == '-':
            unmapped += 1
            continue
        if name == 'LoaderBase':
            bad = check_loader_base(int(a10, 16), int(a11, 16))
            if bad:
                failed += 1
                problems.append((name, a10, a11, '; '.join(bad)))
            else:
                ok += 1
            continue
        state, why = verify(int(a10, 16), int(a11, 16))
        if state == 'ok':
            ok += 1
        elif state == 'skip':
            skipped += 1
        elif name in MANUAL:
            # Verified by other means; see the note beside it in MANUAL.
            excused += 1
        else:
            failed += 1
            problems.append((name, a10, a11, why))

    print('addresses.tsv: %d verified, %d unverifiable (.bss), %d manually confirmed, '
          '%d unmapped, %d FAILED' % (ok, skipped, excused, unmapped, failed))
    for name, a10, a11, why in problems:
        print('  FAIL %-44s %s -> %s   (%s)' % (name, a10, a11, why))
    if failed:
        print('\nA failure means the 1.1 address no longer matches the 1.0 content.')
        print('Re-derive it with:  python3 tools/mapaddr.py <1.0 address>')
        print('If it is a genuine recompile difference confirmed by hand, add the symbol')
        print('to MANUAL in this file with a note saying how it was confirmed.')
    return 1 if failed else 0


def cmd_regcheck():
    """Report every patch site whose surrounding registers were reallocated in 1.1."""
    hits = 0
    for row in rows():
        name, a10, a11 = row[0], row[1], row[2]
        if a11.strip() == '-':
            continue
        moved = regcheck(int(a10, 16), int(a11, 16))
        if not moved:
            continue
        hits += 1
        print('%s  (1.0 %s -> 1.1 %s)' % (name, a10, a11))
        for addr, w10, w11, regs in moved:
            desc = ', '.join('%s r%d->r%d' % (n, x, y) for n, x, y in regs)
            print('    %+4d  %08X -> %08X   %s' % (addr - int(a10, 16), w10, w11, desc))
    print('')
    print('%d patch site(s) sit in code whose registers were reallocated in 1.1.' % hits)
    print('If a hook there reads or writes those registers, it needs a 1.1 variant.')
    return 0


def cmd_snapshot():
    """Print the bytes at every mapped address, both versions side by side.

    --check proves the match succeeded. This is for noticing that it succeeded
    on the wrong thing: a human scanning the two columns will see a site whose
    surroundings clearly are not the same code, which no automated comparison
    can rule out entirely.
    """
    print('%-38s %-10s %-35s %-10s %s' % ('name', 'usa 1.0', 'bytes', 'usa 1.1', 'bytes'))
    for name, a10s, a11s in rows():
        if a11s.strip() == '-':
            print('%-38s %-10s %s' % (name, a10s, 'UNMAPPED'))
            continue
        a10, a11 = int(a10s, 16), int(a11s, 16)
        def dump(img, a):
            o = a - BASE
            if o < 0 or o + 16 > len(img):
                return '(not in image)'
            return ' '.join('%08X' % struct.unpack('<I', img[o + k:o + k + 4])[0]
                            for k in range(0, 16, 4))
        d10, d11 = dump(V10, a10), dump(V11, a11)
        # Compare with branch immediates masked. Every `bl` target moves between
        # builds, so flagging those would put a mark against most rows and train
        # a reader to skip the column that matters.
        o10, o11 = a10 - BASE, a11 - BASE
        differs = (0 <= o10 and o10 + 16 <= len(V10) and 0 <= o11 and o11 + 16 <= len(V11)
                   and mask(V10[o10:o10 + 16], True) != mask(V11[o11:o11 + 16], True))
        flag = '  <- REVIEW: not the same code' if differs else ''
        print('%-38s 0x%06X   %-35s 0x%06X   %s%s' % (name, a10, d10, a11, d11, flag))
    return 0


def cmd_resolve(args):
    bad = 0
    for a in args:
        try:
            addr = int(a, 16)
        except ValueError:
            print('%-12s  not a hex address' % a)
            bad = 1
            continue
        hit, why = resolve(addr)
        if hit is None:
            print('0x%06X  ->  UNRESOLVED  (%s)' % (addr, why))
            bad = 1
        else:
            print('0x%06X  ->  0x%06X   %+#7x   (%s)' % (addr, hit, hit - addr, why))
    return bad


def resolve_any(addr):
    """Resolve by whichever method suits the region the address lives in."""
    if addr >= TEXT_END:
        hit, why, review = resolve_data(addr)
        return hit, why + (' NEEDS-REVIEW' if review else '')
    return resolve(addr)


def cmd_add(name, a):
    addr = int(a, 16)
    hit, why = resolve_any(addr)
    if hit is None:
        print('0x%06X could not be resolved (%s); not added.' % (addr, why))
        return 1
    existing = {r[0] for r in rows()}
    if name in existing:
        print('%r is already in addresses.tsv' % name)
        return 1
    with open(TSV, 'a') as f:
        f.write('%s\t0x%06X\t0x%06X\t%s\n' % (name, addr, hit, why))
    print('added %s\t0x%06X\t0x%06X   (%s)' % (name, addr, hit, why))
    print('addresses.tsv is sorted by 1.0 address; re-sort if you care.')
    return 0


def main():
    args = sys.argv[1:]
    if not args:
        sys.exit(__doc__)
    if args[0] == '--check':
        return cmd_check()
    if args[0] == '--regcheck':
        return cmd_regcheck()
    if args[0] == '--snapshot':
        return cmd_snapshot()
    if args[0] == '--add':
        if len(args) != 3:
            sys.exit('usage: mapaddr.py --add NAME 0xADDRESS')
        return cmd_add(args[1], args[2])
    return cmd_resolve(args)


if __name__ == '__main__':
    sys.exit(main())
