.arm
.align 4

.macro SVC_BEGIN name
	.section .loader.\name, "ax", %progbits
	.global \name
	.type \name, %function
	.align 2
	.cfi_startproc
\name:
.endm

.macro SVC_END
	.cfi_endproc
.endm

SVC_BEGIN svcOpenProcess
	push {r0}
	svc 0x33
	pop {r2}
	str r1, [r2]
	bx  lr
SVC_END

SVC_BEGIN svcGetProcessId
	str r0, [sp, #-0x4]!
	svc 0x35
	ldr r3, [sp], #4
	str r1, [r3]
	bx  lr
SVC_END

SVC_BEGIN svcBreak
	svc 0x3C
	bx  lr
SVC_END

SVC_BEGIN svcControlProcessMemory
	push {r4-r5}
	ldr r4, [sp, #0x8]
	ldr r5, [sp, #0xC]
	svc 0x70
	pop {r4-r5}
	bx  lr
SVC_END

SVC_BEGIN svcSendSyncRequest
	svc 0x32
	bx  lr
SVC_END

SVC_BEGIN svcCreateMemoryBlock
	str r0, [sp, #-4]!
	ldr r0, [sp, #4]
	svc 0x1E
	ldr r2, [sp], #4
	str r1, [r2]
	bx  lr
SVC_END

SVC_BEGIN svcArbitrateAddressNoTimeout
	svc 0x22
	bx  lr
SVC_END

SVC_BEGIN svcReleaseMutex
	svc 0x14
	bx  lr
SVC_END

SVC_BEGIN svcUnmapMemoryBlock
	svc 0x20
	bx  lr
SVC_END

SVC_BEGIN svcMapMemoryBlock
	svc 0x1F
	bx  lr
SVC_END

SVC_BEGIN svcDuplicateHandle
	str r0, [sp, #-0x4]!
	svc 0x27
	ldr r3, [sp], #4
	str r1, [r3]
	bx  lr
SVC_END
