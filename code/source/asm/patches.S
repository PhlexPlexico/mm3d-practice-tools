#include "game/addresses.h"

@ Overwrites applied on top of vanilla instructions. Each section is pinned to
@ an absolute address by mm.ld. The comment above each stub is the instruction
@ it replaces; hooks that re-execute it depend on that staying accurate.

.arm

@ --- (a) bootstrap ------------------------------------------------------------

@ 0x100000, vanilla: bl 0x100024   (re-executed by hook_into_loader)
.section .patch_loader
.global loader_patch
loader_patch:
    b hook_into_loader

@ 0x10001C, vanilla: bl 0x103EC8   (re-executed by hook_Start)
.section .patch_startHeap
.global patch_startHeap
patch_startHeap:
    bl hook_Start

@ --- (b) entry points ---------------------------------------------------------

@ 0x10676C, vanilla: ldr r1, [r0, #0x138]
.section .patch_MainLoop
.global patch_MainLoop
patch_MainLoop:
    b hook_MainLoop

@ 0x107148, vanilla: nop -- a free slot in the per-frame render path.
.section .patch_DrawMenu
.global patch_DrawMenu
patch_DrawMenu:
    b hook_DrawMenu

@ 0x174A6C, vanilla: add r10, r5, #0x10
.section .patch_PreActorCalc
.global patch_PreActorCalc
patch_PreActorCalc:
    bl hook_PreActorCalc

@ 0x174E08, vanilla: add r3, r5, #0x10
.section .patch_PostActorCalc
.global patch_PostActorCalc
patch_PostActorCalc:
    bl hook_PostActorCalc

@ 0x59BA10, vanilla: tst r0, r1
.section .patch_ReadGamePad
.global patch_ReadGamePad
patch_ReadGamePad:
    b hook_readGamePad

@ 0x59BA14, vanilla: beq 0x59BB60 -- skip the game's own button handling.
@ readPadInput replaces it entirely.
.section .patch_DisableExistingTrigger
.global patch_DisableExistingTrigger
patch_DisableExistingTrigger:
    b ADDR_DisableExistingTriggerTarget

@ --- (c) self-contained overwrites --------------------------------------------

@ 0x1D32E0, vanilla: strb r0, [r5, #0xE3B]. r5 is Player+0x11000, so this and
@ the two stores after clear sword_active_timer / sword_active. Skipping them is
@ half of ISG; calc() re-arms the fields each frame for the other half.
.section .patch_ISGCrouchStabOne
.global patch_ISGCrouchStabOne
patch_ISGCrouchStabOne:
    b ADDR_ISGCrouchStabOneTarget

@ 0x1DBEA4, vanilla: str r1, [r6, #0xDB4] -- the same clear, other path.
.section .patch_ISGCrouchStabTwo
.global patch_ISGCrouchStabTwo
patch_ISGCrouchStabTwo:
    b ADDR_ISGCrouchStabTwoTarget

@ 0x1166C8, vanilla: tst r0, #0x4000 -- skip the block folding ZL into ZR.
.section .patch_DecoupleZlZr
.global patch_DecoupleZlZr
patch_DecoupleZlZr:
    b ADDR_DecoupleZlZrTarget

@ 0x121EE8, vanilla: cmp r0, #0
.section .patch_DecoupleStartSelect
.global patch_DecoupleStartSelect
patch_DecoupleStartSelect:
    nop

@ 0x1404E8, vanilla: beq 0x140508. The setter is called with r1 = 2 to force
@ Surround; r0 already holds the console's own setting, so always branching to
@ the apply call installs that instead.
.section .patch_FixSurroundSound
.global patch_FixSurroundSound
patch_FixSurroundSound:
    b ADDR_SurroundSoundApply

@ 0x5C19E4, vanilla: tst r1, #2 (B). Widen to B | Select so Select closes the
@ item screen it opens. Not Start -- that opens the notebook.
.section .patch_ItemCloseOnSelect
.global patch_ItemCloseOnSelect
patch_ItemCloseOnSelect:
    tst r1, #6

@ --- Stone Tower blocks and elegy statues -------------------------------------

@ Data, not instructions. .float rather than the old .hks files' raw bytes.

@ 0x2AC634, vanilla: 20.0 -- block movement speed.
.section .patch_FasterBlockMovement
.global patch_FasterBlockMovement
patch_FasterBlockMovement:
    .float 50.0

@ 0x2D0C0C, vanilla: 40.0 -- speed on the way back.
.section .patch_FasterBlockMovementBack
.global patch_FasterBlockMovementBack
patch_FasterBlockMovementBack:
    .float 60.0

@ 0x5187A4, vanilla: bl 0x44A67C
.section .patch_ElegyStatueNoDarkEffect
.global patch_ElegyStatueNoDarkEffect
patch_ElegyStatueNoDarkEffect:
    nop

@ 0x5187D0, vanilla: strh r0, [r7, #0xE0]
.section .patch_ElegyStatueNoDarkEffectTwo
.global patch_ElegyStatueNoDarkEffectTwo
patch_ElegyStatueNoDarkEffectTwo:
    nop
