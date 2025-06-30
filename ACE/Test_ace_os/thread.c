/******************************************************************************/
/*! @addtogroup Group2
    @file       thread.c
    @brief      
    @date       2025/06/30
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#include "thread.h"
#include <stdlib.h>
#include <stdint.h>

#define SCS_BASE                        (uint32_t) (0xE000E000)
#define SCB_BASE                        (SCS_BASE + 0x0D00)
#define SCB_ICSR                        (volatile uint32_t *) (SCB_BASE + 0x004)
#define SCB_ICSR_PENDSVSET              (uint32_t) (1 << 28)

#define MAX_TASKS 2
#define STACK_SIZE 256
/* Exception return behavior */
#define HANDLER_MSP	0xFFFFFFF1
#define THREAD_MSP	0xFFFFFFF9
#define THREAD_PSP	0xFFFFFFFD

typedef struct {
	void *stack;
	void *orig_stack;
	uint8_t in_use;
} tcb_t;

static tcb_t tasks[MAX_TASKS];
static uint32_t lastTask;

/* Caution: Without naked attribute, GCC will normally push r7 which is used
 * for stack pointer. If so, after restoring the tasks' context, we will get
 * wrong stack pointer. PendSV handles calling convention itself.
 */
void __attribute__((naked)) PendSV_Handler()
{
	/* Save the old task's context[1]*/
	asm volatile("mrs   r0, psp\n"
	             "stmdb r0!, {r4-r11, lr}\n");
	/* To get the task pointer address from result r0 */
	asm volatile("mov   %0, r0\n" : "=r" (tasks[lastTask].stack));

	/* Find a new task to run */
	while (1) {
		lastTask++;
		if (lastTask == MAX_TASKS)
			lastTask = 0;
		if (tasks[lastTask].in_use) {
			/* Move the task's stack pointer address into r0 */
			asm volatile("mov r0, %0\n" : : "r" (tasks[lastTask].stack));
			/* Restore the new task's context and jump to the task */
			asm volatile("ldmia r0!, {r4-r11, lr}\n"
			             "msr psp, r0\n"
			             "bx lr\n");
		}
	}
}

void SysTick_Handler()
{
	*SCB_ICSR |= SCB_ICSR_PENDSVSET;
}

/* As PendSV does, this function also switches context and
 * maintain assembly on its own. This avoids the compiler
 * modifying register at prologue/epilogue sequences and
 * corrupts inline-assembly usage.
 */
void __attribute__((naked)) thread_start()
{
	lastTask = 0;

	/* Reset APSR before context switch.
	 * Make sure we have a _clean_ PSR for the task.
	 */
	asm volatile("mov r0, #0\n"
	             "msr APSR_nzcvq, r0\n");
	/* To bridge the variable in C and the register in ASM,
	 * move the task's stack pointer address into r0.
	 * http://www.ethernut.de/en/documents/arm-inline-asm.html
	 */
	asm volatile("mov r0, %0\n" : : "r" (tasks[lastTask].stack));
	asm volatile("msr psp, r0\n"
	             "mov r0, #3\n"
	             "msr control, r0\n"
	             "isb\n");
	/* This is how we simulate stack handling that pendsv_handler
	 * does. Thread_create sets 17 entries in stack, and the 9
	 * entries we pop here will be pushed back in pendsv_handler
	 * in the same order.
	 *
	 *
	 *                      pop {r4-r11, lr}
	 *                      ldr r0, [sp]
	 *          stack
	 *  offset -------
	 *        |   16  | <- Reset value of PSR
	 *         -------
	 *        |   15  | <- Task entry
	 *         -------
	 *        |   14  | <- LR for task
	 *         -------
	 *        |  ...  |                             register
	 *         -------                              -------
	 *        |   9   | <- Task argument ---->     |   r0  |
	 * psp after pop--<                             -------
	 *        |   8   | <- EXC_RETURN    ---->     |   lr  |
	 *         -------                              -------
	 *        |   7   |                            |  r11  |
	 *         -------                              -------
	 *        |  ...  |                            |  ...  |
	 *         -------                              -------
	 *        |   0   |                            |   r4  |
	 * psp ->  -------                              -------
	 *
	 * Instead of "pop {r0}", use "ldr r0, [sp]" to ensure consistent
	 * with the way how PendSV saves _old_ context[1].
	 */
	asm volatile("pop {r4-r11, lr}\n"
	             "ldr r0, [sp]\n");
	/* Okay, we are ready to run first task, get address from
	 * stack[15]. We just pop 9 register so #24 comes from
	 * (15 - 9) * sizeof(entry of sp) = 6 * 4.
	 */
	asm volatile("ldr pc, [sp, #24]\n");

	/* Never reach here */
	while(1);
}

int thread_create(void (*run)(void *), void *userdata)
{
	/* Find a free thing */
	int threadId = 0;
	uint32_t *stack;

	for (threadId = 0; threadId < MAX_TASKS; threadId++) {
		if (tasks[threadId].in_use == 0)
			break;
	}

	if (threadId == MAX_TASKS)
		return -1;

	/* Create the stack */
	stack = (uint32_t *) malloc(STACK_SIZE * sizeof(uint32_t));
	tasks[threadId].orig_stack = stack;
	if (stack == 0)
		return -1;

	stack += STACK_SIZE - 17; /* End of stack, minus what we are about to push */
	stack[8] = (uint32_t) THREAD_PSP;
	stack[9] = (uint32_t) userdata;
	stack[14] = (uint32_t) &thread_self_terminal;
	stack[15] = (uint32_t) run;
	stack[16] = (uint32_t) 0x01000000; /* PSR Thumb bit */

	/* Construct the control block */
	tasks[threadId].stack = stack;
	tasks[threadId].in_use = 1;

	return threadId;
}

void thread_kill(uint32_t thread_id)
{
	tasks[thread_id].in_use = 0;

	/* Free the stack */
	free(tasks[thread_id].orig_stack);
}

void thread_self_terminal()
{
	/* This will kill the stack.
	 * For now, disable context switches to save ourselves.
	 */
	asm volatile("cpsid i\n");
	thread_kill(lastTask);
	asm volatile("cpsie i\n");

	/* And now wait for death to kick in */
	while (1);
}

/* [1] Exception entry only saves R0-R4, R12, LR, PC and xPSR,
 *     which means PendSV has to save other context (R4-R11) itself to
 *     complete context switch.
 *     Also, pushing LR (=EXC_RETURN) into thread stack before switching
 *     task is needed in order to perform exception return next time the task
 *     is selected to run.
 *     Reference:
 *         Cortex-M4 Devices: Generic User Guide (ARM DUI 0553A):
 *         2.3.7 Exception entry and return
 */