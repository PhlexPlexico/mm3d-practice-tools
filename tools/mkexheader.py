"""Generate the patched exheader from the game's own vanilla one.

The exheader has to be changed in three ways before the patch will run:

  * the new-code region at 0x7D0000 must fall inside mapped memory,
  * the process must be allowed to call svcControlProcessMemory, which the
    loader uses to make that region executable,
  * and it must be allowed to touch the SD card, for save states and configs.

Console and emulator need different files. On console the .data code set is
grown to cover the region; Emulator leaves .data alone and grows .bss instead.
Both end up covering 0x7D0000, by different routes.

One field is version-dependent and is the reason this reads a vanilla exheader
rather than shipping two blobs: USA 1.1's .rodata is 1880 bytes larger than
1.0's (0x2DD28 against 0x2D5D0). Declaring 1.0's size on a 1.1 build truncates
the segment, which is not a crash at boot -- it is wrong data much later.

    python3 tools/mkexheader.py --vanilla bin/exheader1.0.bin --out exheader.bin
    python3 tools/mkexheader.py --vanilla bin/exheader1.0.bin --out exheader_emulator.bin --emulator

Re-running on an already-patched exheader is harmless; every edit is idempotent.
"""
import struct
import sys

# --- System Control Info -----------------------------------------------------
OFF_TEXT_SIZE = 0x18
OFF_DATA_ADDR = 0x30
OFF_DATA_PAGES = 0x34
OFF_DATA_SIZE = 0x38
OFF_BSS_SIZE = 0x3C

# --- Access Control Info. The second copy is the access descriptor, which caps
# what the first may ask for; the vanilla game already permits SD access there.
ACI = (0x200, 0x600)
OFF_EXTDATA_ID = 0x30      # from an ACI base
OFF_FS_ACCESS = 0x48
OFF_OTHER_ATTRIBUTES = 0x4F
OFF_KERNEL_CAPS = 0x170    # 28 descriptors of 4 bytes
NUM_KERNEL_CAPS = 28

FS_DIRECT_SDMC = 1 << 7
FS_DIRECT_SDMC_WRITE = 1 << 15
STORAGE_OTHER_ATTRIBUTE_EMULATOR = 0x02

# The loader lives in the padding past the vanilla text size, so the segment has
# to be declared out to the end of its last page or those bytes never load.
TEXT_SIZE = 0x51D000

# Console: grow .data to 0x64B000..0x8A1000.
CONSOLE_DATA_PAGES = 0x256
CONSOLE_DATA_SIZE = 0x300000
CONSOLE_BSS_SIZE = 0x84000

# Emulator: leave .data vanilla and grow .bss to reach 0x923938 instead.
EMULATOR_BSS_END = 0x923938

NEWCODE_BASE = 0x7D0000

# Syscall mask descriptor: bits 26-24 select a group of 24 syscalls, bits 23-0
# the mask within it. Group 4 covers 0x60-0x77, and bit 16 is syscall 0x70 --
# svcControlProcessMemory. Vanilla grants groups 0-2 only.
CAP_SVC_CONTROL_PROCESS_MEMORY = 0xF4010000
CAP_EMPTY = 0xFFFFFFFF
CAP_SYSCALL_MASK = 0xF8000000
CAP_SYSCALL_PREFIX = 0xF0000000

EXTDATA_ID = 0x125600


def arg(flag, default=None):
    return sys.argv[sys.argv.index(flag) + 1] if flag in sys.argv else default


def u32(b, off):
    return struct.unpack('<I', b[off:off + 4])[0]


def put32(b, off, val):
    struct.pack_into('<I', b, off, val)


def grant_syscall(b):
    """Add the svcControlProcessMemory capability, after the existing masks.

    Only the first ACI. The second is the access descriptor, which is signed and
    normally caps what the first may request -- it does not permit this syscall
    either. Luma skips that check when game patching is on, which is the only
    way any of this runs, so the requested set is what takes effect.
    """
    for base in ACI[:1]:
        caps_at = base + OFF_KERNEL_CAPS
        caps = [u32(b, caps_at + i * 4) for i in range(NUM_KERNEL_CAPS)]
        if CAP_SVC_CONTROL_PROCESS_MEMORY in caps:
            continue
        if CAP_EMPTY not in caps:
            sys.exit('no free kernel capability slot to grant syscall 0x70')
        last_mask = max(i for i, c in enumerate(caps)
                        if c & CAP_SYSCALL_MASK == CAP_SYSCALL_PREFIX)
        caps.insert(last_mask + 1, CAP_SVC_CONTROL_PROCESS_MEMORY)
        caps.pop()                      # drop one trailing empty slot
        for i, c in enumerate(caps):
            put32(b, caps_at + i * 4, c)


def main():
    vanilla = arg('--vanilla')
    out = arg('--out')
    emulator = '--emulator' in sys.argv
    if not vanilla or not out:
        sys.exit(__doc__)

    b = bytearray(open(vanilla, 'rb').read())
    if len(b) != 0x800:
        sys.exit('%s is %d bytes; an exheader is 2048' % (vanilla, len(b)))

    put32(b, OFF_TEXT_SIZE, TEXT_SIZE)

    data_addr = u32(b, OFF_DATA_ADDR)
    if emulator:
        # .data stays as the game had it; .bss is what reaches over the region.
        data_end = data_addr + u32(b, OFF_DATA_PAGES) * 0x1000
        put32(b, OFF_BSS_SIZE, EMULATOR_BSS_END - data_end)
    else:
        put32(b, OFF_DATA_PAGES, CONSOLE_DATA_PAGES)
        put32(b, OFF_DATA_SIZE, CONSOLE_DATA_SIZE)
        put32(b, OFF_BSS_SIZE, CONSOLE_BSS_SIZE)

    grant_syscall(b)

    for base in ACI:
        fs = int.from_bytes(b[base + OFF_FS_ACCESS:base + OFF_FS_ACCESS + 7], 'little')
        fs |= FS_DIRECT_SDMC | FS_DIRECT_SDMC_WRITE
        b[base + OFF_FS_ACCESS:base + OFF_FS_ACCESS + 7] = fs.to_bytes(7, 'little')
        if emulator:
            b[base + OFF_OTHER_ATTRIBUTES] = STORAGE_OTHER_ATTRIBUTE_EMULATOR
        struct.pack_into('<Q', b, base + OFF_EXTDATA_ID, EXTDATA_ID)

    mapped_end = data_addr + u32(b, OFF_DATA_PAGES) * 0x1000 + u32(b, OFF_BSS_SIZE)
    if mapped_end <= NEWCODE_BASE:
        sys.exit('exheader maps only to 0x%06X, short of the new code at 0x%06X'
                 % (mapped_end, NEWCODE_BASE))

    open(out, 'wb').write(bytes(b))
    print('%s: %s, ro 0x%X, mapped to 0x%06X'
          % (out, 'emulator' if emulator else 'console',
             u32(b, 0x28), mapped_end))

    reference = arg('--selftest')
    if reference:
        want = open(reference, 'rb').read()
        if bytes(b) == want:
            print('  selftest: matches %s exactly' % reference)
        else:
            diff = [i for i in range(0x800) if b[i] != want[i]]
            sys.exit('  selftest: differs from %s at %d bytes: %s'
                     % (reference, len(diff), ', '.join('0x%03X' % d for d in diff[:12])))


if __name__ == '__main__':
    main()
