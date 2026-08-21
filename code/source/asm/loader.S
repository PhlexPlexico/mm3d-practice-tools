#include "game/addresses.h"

@ Bootstrap, at 0x100000. Runs before the new-code region is executable, so it
@ has to live in the padding after the text segment -- the only slack already
@ mapped and runnable. USA 1.0 leaves 628 bytes there, USA 1.1 leaves 76, which
@ is why this is assembly and not the ~300-byte C loader it replaces.
@
@ SVC conventions:
@   svcGetProcessId          r1 = handle -> pid in r1
@   svcOpenProcess           r1 = pid    -> handle in r1
@   svcControlProcessMemory  r0 = handle, r1/r2 = addr, r3 = size, r4 = op,
@                            r5 = permissions
@ The first two chain without a move.

.arm

.equ CUR_PROCESS_PSEUDO_HANDLE, 0xFFFF8001
.equ MEMOP_PROT,                6
.equ MEMPERM_RWX,               7

.equ SVC_OPEN_PROCESS,          0x33
.equ SVC_GET_PROCESS_ID,        0x35
.equ SVC_BREAK,                 0x3C
.equ SVC_CONTROL_PROCESS_MEMORY, 0x70

.section .loader.hook_into_loader, "ax", %progbits
.global hook_into_loader
.type hook_into_loader, %function
.align 2
hook_into_loader:
    push {r0-r5, lr}

    ldr  r1, =CUR_PROCESS_PSEUDO_HANDLE
    svc  #SVC_GET_PROCESS_ID
    svc  #SVC_OPEN_PROCESS
    mov  r0, r1                        @ process handle

    @ Immediate, not a literal: the pool costs four bytes 1.1 does not have.
    @ mm.ld asserts the base still matches.
    mov  r1, #0x7D0000
    mov  r2, r1
    ldr  r3, =__newcode_map_size
    mov  r4, #MEMOP_PROT
    mov  r5, #MEMPERM_RWX
    svc  #SVC_CONTROL_PROCESS_MEMORY

    @ Break with the result in r0, rather than letting it surface later as a
    @ prefetch abort into the region that was never made executable.
    cmp  r0, #0
    svclt #SVC_BREAK

    pop  {r0-r5, lr}
    bl   ADDR_LoaderDisplacedBl                      @ vanilla instruction displaced from 0x100000
    b    ADDR_LoaderReturn
.size hook_into_loader, . - hook_into_loader
