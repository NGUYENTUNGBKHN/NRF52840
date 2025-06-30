
.thumb
.syntax unified

.macro save_kernel_state
	mrs ip, psr
	push {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}
.endm

.type SVC_Handler, %function
.global SVC_Handler
.type SysTick_Handler, %function
.global SysTick_Handler
SysTick_Handler:
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
    save_kernel_state

    /* Load user state */
    ldmia r0!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}

    msr psp, r0                                         /* move r0 to psp */

    /* jump to user task */
    bx lr

.global task_init_evn
task_init_evn:
    save_kernel_state

    msr psp, r0
    mov r0, #3
	msr control, r0
    isb
    bl syscall
    bx lr
