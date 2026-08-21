"""Encode the linked ELF's sections into an IPS patch for MM3D's code.bin.

Every byte this emits is written directly over the game's executable, so the guard
in check_manifest() is not optional: a section that the linker placed somewhere we
did not ask for is silently-corrupting ROM, and there is no --gc-sections in
LDFLAGS to clean up strays.

Usage: python3 patch.py code.elf [-o basecode.ips] [--ld mm.ld]
"""
import os
import re
import struct
import subprocess
import sys

BASE = 0x100000

elf = sys.argv[1]
out = sys.argv[sys.argv.index('-o') + 1] if '-o' in sys.argv else 'basecode.ips'
ldPath = sys.argv[sys.argv.index('--ld') + 1] if '--ld' in sys.argv else 'mm.ld'


def devkit(tool):
    return os.path.join(os.environ['DEVKITARM'], 'bin', 'arm-none-eabi-' + tool)


def sections_of(path):
    """(name, vaddr, fileOffset, size) for every allocated section with a real address."""
    res = subprocess.run([devkit('objdump'), '--section-headers', path],
                         stdout=subprocess.PIPE, check=True)
    found = []
    for line in res.stdout.decode('utf-8', 'replace').splitlines():
        f = line.split()
        # "Idx Name Size VMA LMA FileOff Algn"
        if len(f) >= 6 and f[0].isdigit():
            name, size, vma, fileoff = f[1], int(f[2], 16), int(f[3], 16), int(f[5], 16)
            if vma != 0 and size != 0:
                found.append((name, vma, fileoff, size))
    return found


def manifest_of(path):
    allowed = {}
    for line in open(path):
        line = line.split('/*')[0]
        m = re.match(r'\s*(\.[\w.]+)\s*(0x[0-9A-Fa-f]+)?\s*:', line)
        if m:
            allowed[m.group(1)] = int(m.group(2), 16) if m.group(2) else None
    return allowed


def check_manifest(sections, allowed):
    problems = []
    for name, vaddr, _, size in sections:
        # ld appends a suffix when it splits an output section; match the declared stem.
        stem = name if name in allowed else next(
            (k for k in allowed if name == k or name.startswith(k + '.')), None)
        if stem is None:
            problems.append('%-28s @0x%06X (%d bytes) is not declared in %s'
                            % (name, vaddr, size, ldPath))
            continue
        want = allowed[stem]
        if want is not None and vaddr != want:
            problems.append('%-28s @0x%06X but %s pins it at 0x%06X'
                            % (name, vaddr, ldPath, want))
    if problems:
        sys.exit('patch.py: refusing to emit a patch containing undeclared sections.\n'
                 'These bytes would be written over the game and corrupt it:\n  '
                 + '\n  '.join(problems)
                 + '\n\nEither add a rule for it to %s or remove the code that'
                   ' created it.' % ldPath)


IPS_RAW_MAX = 0xFFFF
IPS_RLE_MAX = 0xFFFF
IPS_RLE_MIN_RUN = 14
# A record starting at this offset would be read as the "EOF" footer and silently
# truncate the patch. Nothing currently lands here, so refuse rather than corrupt.
IPS_EOF_OFFSET = 0x454F46


def off(vaddr):
    offset = vaddr - BASE
    if not 0 <= offset <= 0xFFFFFF:
        raise ValueError("vaddr 0x%X is outside the 3-byte IPS offset range" % vaddr)
    if offset == IPS_EOF_OFFSET:
        raise ValueError("record at vaddr 0x%X would be read as the IPS EOF footer" % vaddr)
    return struct.pack(">I", offset)[1:]


sz = lambda size: struct.pack(">H", size)


def ips_raw(vaddr, chunk):
    return off(vaddr) + sz(len(chunk)) + chunk


def ips_rle(vaddr, length, value):
    return off(vaddr) + sz(0) + sz(length) + bytes([value])


def ips_encode(vaddr, data):
    """Encode one contiguous block, collapsing long runs of one byte into RLE records."""
    out = bytearray()
    spanStart = 0
    i = 0

    def flushRaw(end):
        start = spanStart
        while start < end:
            stop = min(start + IPS_RAW_MAX, end)
            out.extend(ips_raw(vaddr + start, data[start:stop]))
            start = stop

    while i < len(data):
        value = data[i]
        runEnd = i
        while runEnd < len(data) and data[runEnd] == value:
            runEnd += 1
        if runEnd - i >= IPS_RLE_MIN_RUN:
            flushRaw(i)
            start = i
            while start < runEnd:
                length = min(runEnd - start, IPS_RLE_MAX)
                out.extend(ips_rle(vaddr + start, length, value))
                start += length
            spanStart = runEnd
        i = runEnd
    flushRaw(len(data))
    return bytes(out)


sections = [s for s in sections_of(elf) if '.eh_frame' not in s[0]]
check_manifest(sections, manifest_of(ldPath))

ips = b'PATCH'
sectionBytes = 0
with open(elf, 'rb') as e:
    for name, vaddr, offset, size in sections:
        e.seek(offset, 0)
        data = e.read(size)
        if data:
            print('%08X %08X %s' % (vaddr, vaddr + size, name))
            ips += ips_encode(vaddr, data)
            sectionBytes += len(data)
ips += b'EOF'

with open(out, 'wb') as patchFile:
    patchFile.write(ips)
print("encoded %d bytes of section data into %s (%d bytes)" % (sectionBytes, out, len(ips)))
