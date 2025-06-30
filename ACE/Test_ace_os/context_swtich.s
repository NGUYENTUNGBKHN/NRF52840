
.thumb
.syntax unified

.type SVC_Handler, %function
.global SVC_Handler
SVC_Handler:
	/* save user state */
	mrs r0, psp
	stmdb r0!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}

	/* load kernel state */
	pop {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}
	msr psr, ip

	bx lr

.global activate
activate:
    /* Save kernel state */
    mrs ip, psr                                         /* move psr to ip(R12) */
    push {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}

    /* Load user state */
    ldmia r0!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}

    msr psp, r0                                         /* move r0 to psp */

    mov r0, #0xfffffff0
    cmp lr, r0

    ittt ls
    movls r0, #3
	msrls control, r0
	isbls

    /* jump to user task */
    bx lr
