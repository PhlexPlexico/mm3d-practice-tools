#include "game/addresses.h"

@ Trampolines for the patch stubs in patches.s.
@
@ These live in the new-code region (plain .text), so they may be any length.
@ The shape is fixed: preserve every register the vanilla code could care about,
@ call into C++, restore, re-execute the instruction the patch overwrote, then
@ branch back to the instruction after the patch site.
@
@ The bootstrap itself lives in source/asm/loader.s, which has a much tighter
@ size budget -- see the note there.

.arm
.text

.global hook_Start
hook_Start:
    push {r0-r12, lr}
    bl _start
    pop {r0-r12, lr}
    b ADDR_StartHeapReturn        @ vanilla: bl 0x103EC8 -- the link register is unused here

.global hook_MainLoop
hook_MainLoop:
    push {r0-r12, lr}
    bl calc
    pop {r0-r12, lr}
    ldr r1, [r0,#0x138]
    b ADDR_MainLoopReturn

.global hook_DrawMenu
hook_DrawMenu:
    push {r0-r12, lr}
    bl DrawMenu
    pop {r0-r12, lr}
    nop                @ vanilla instruction displaced from 0x107148
    b ADDR_DrawMenuReturn

.global hook_PreActorCalc
hook_PreActorCalc:
    push {r0-r12, lr}
    bl PreActorCalc
    pop {r0-r12, lr}
    add r10, r5, #0x10
    bx lr

.global hook_PostActorCalc
hook_PostActorCalc:
    push {r0-r12, lr}
    bl PostActorCalc
    pop {r0-r12, lr}
    add r3, r5, #0x10
    bx lr

.global hook_readGamePad
hook_readGamePad:
    push {r0-r12, lr}
    bl readPadInput
    pop {r0-r12, lr}
    tst r0, r1
    b ADDR_DisableExistingTrigger_59BA14
