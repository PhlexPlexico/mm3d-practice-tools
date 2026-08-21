"""Apply an IPS to a pristine code.bin and prove it only touched what it declared.

The build's job is to write a handful of small patches over the game plus one
block of new code. This checks that claim byte for byte, offline: apply the
patch, diff against the original, and fail if any changed byte falls outside a
section the linker actually emitted, or if the result outgrows the region the
exheader maps.

Together with patch.py's manifest check (ELF sections must all be declared in
mm.ld) this closes the loop: mm.ld bounds the ELF, and the ELF bounds the IPS.

    python3 tools/verify_ips.py code/basecode.ips bin/code1.0.bin \
        --elf code/code.elf --exheader romfs/exheader.bin
"""
import os
import struct
import subprocess
import sys

BASE = 0x100000


def arg(flag, default=None):
    return sys.argv[sys.argv.index(flag) + 1] if flag in sys.argv else default


def parse_ips(blob):
    if blob[:5] != b'PATCH':
        raise ValueError('not an IPS file (bad magic)')
    i = 5
    while True:
        if blob[i:i + 3] == b'EOF':
            if i + 3 != len(blob):
                raise ValueError('trailing bytes after the EOF footer')
            return
        if i + 5 > len(blob):
            raise ValueError('truncated record header')
        off = int.from_bytes(blob[i:i + 3], 'big')
        size = int.from_bytes(blob[i + 3:i + 5], 'big')
        i += 5
        if size == 0:
            run = int.from_bytes(blob[i:i + 2], 'big')
            yield off, bytes([blob[i + 2]]) * run
            i += 3
        else:
            yield off, blob[i:i + size]
            i += size


def elf_sections(path):
    """(name, vaddr, size) for every section the linker gave a real address."""
    objdump = os.path.join(os.environ['DEVKITARM'], 'bin', 'arm-none-eabi-objdump')
    res = subprocess.run([objdump, '--section-headers', path],
                         stdout=subprocess.PIPE, check=True)
    out = []
    for line in res.stdout.decode('utf-8', 'replace').splitlines():
        f = line.split()
        if len(f) >= 6 and f[0].isdigit():
            size, vma = int(f[2], 16), int(f[3], 16)
            if vma and size:
                out.append((f[1], vma, size))
    return out


def mapped_end(exheader):
    """Highest virtual address the exheader keeps mapped, and the file size that implies."""
    d = open(exheader, 'rb').read()
    _, tp, _ = struct.unpack('<III', d[0x10:0x1C])
    _, rp, _ = struct.unpack('<III', d[0x20:0x2C])
    da, dp, _ = struct.unpack('<III', d[0x30:0x3C])
    return da + dp * 0x1000, (tp + rp + dp) * 0x1000


def main():
    ipsPath, origPath = sys.argv[1], sys.argv[2]
    elf = arg('--elf', 'code/code.elf')
    exheader = arg('--exheader')

    base = open(origPath, 'rb').read()
    records = list(parse_ips(open(ipsPath, 'rb').read()))

    size = len(base)
    for off, data in records:
        size = max(size, off + len(data))
    patched = bytearray(base) + bytearray(size - len(base))
    for off, data in records:
        patched[off:off + len(data)] = data

    sections = elf_sections(elf)
    problems = []

    # 1. Every changed byte must sit inside some emitted section.
    changed = [i for i in range(size)
               if (base[i] if i < len(base) else 0) != patched[i]]
    def inside(vaddr):
        return any(v <= vaddr < v + s for _, v, s in sections)
    stray = [i + BASE for i in changed if not inside(i + BASE)]

    print('%s applied to %s' % (ipsPath, origPath))
    print('  %d records, %d bytes changed, %d sections'
          % (len(records), len(changed), len(sections)))
    for name, v, s in sections:
        print('    0x%06X..0x%06X %7d  %s' % (v, v + s, s, name))

    if stray:
        lo, hi = min(stray), max(stray)
        problems.append('%d changed bytes lie outside every emitted section '
                        '(0x%06X..0x%06X)' % (len(stray), lo, hi))

    # 2. The result must fit the region the exheader maps.
    if exheader:
        vend, implied = mapped_end(exheader)
        print('  exheader maps up to 0x%06X (code.bin would be %d bytes)'
              % (vend, implied))
        top = size + BASE
        if top > vend:
            problems.append('patched image reaches 0x%06X, past the 0x%06X the '
                            'exheader maps' % (top, vend))
        else:
            print('  patched image reaches 0x%06X, %d bytes of headroom'
                  % (top, vend - top))

    if problems:
        print('\nFAIL')
        for p in problems:
            print('  ' + p)
        return 1
    print('\nOK: every changed byte lies inside an emitted section.')
    return 0


if __name__ == '__main__':
    sys.exit(main())
