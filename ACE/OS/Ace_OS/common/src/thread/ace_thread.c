/******************************************************************************/
/*! @addtogroup Group2
    @file       ace_thread.c
    @brief      
    @date       2025/07/03
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#include "ace_api.h"
#include "ace_thread.h"

uint32_t _tx_thread_created_count = 0;

void _ace_thread_exit();

ACE_THREAD ace_thread[MAX_TASKS];
ACE_THREAD *_ace_thread_creatd_ptr;
uint32_t lastTask;

// void __attribute__((naked)) PendSV_Handler()
// {
// 	/* Save the old task's context[1]*/
// 	asm volatile("mrs   r0, psp\n"
// 	             "stmdb r0!, {r4-r11, lr}\n");
// 	/* To get the task pointer address from result r0 */
// 	asm volatile("mov   %0, r0\n" : "=r" (ace_thread[lastTask].ace_thread_stack_ptr));

// 	/* Find a new task to run */
// 	while (1) {
// 		lastTask++;
// 		if (lastTask == MAX_STACKS)
// 			lastTask = 0;
// 		if (ace_thread[lastTask].ace_in_use) 
//         {
// 			/* Move the task's stack pointer address into r0 */
// 			asm volatile("mov r0, %0\n" : : "r" (ace_thread[lastTask].ace_thread_stack_ptr));
// 			/* Restore the new task's context and jump to the task */
// 			asm volatile("ldmia r0!, {r4-r11, lr}\n"
// 			             "msr psp, r0\n"
// 			             "bx lr\n");
// 		}
// 	}
// }

// void SysTick_Handler()
// {
// 	*SCB_ICSR |= SCB_ICSR_PENDSVSET;
// }

// void __attribute__((naked)) _ace_thread_start()
// {
//     lastTask = 0;

//     /* Reset APSR register. */
//     asm volatile("MOV r0, #0\n"
//                  "MSR APSR_nzcvq, r0\n");
//     /* move the task's stack pointer address into r0. */
//     asm volatile("mov r0, %0\n" : : "r" (ace_thread[lastTask].ace_thread_stack_ptr));
// 	asm volatile("msr psp, r0\n"
// 	             "mov r0, #3\n"
// 	             "msr control, r0\n"
// 	             "isb\n");

//     asm volatile("pop {r4-r11, lr}\n"
// 	             "ldr r0, [sp]\n");
    
//     asm volatile("ldr pc, [sp, #24]\n");

//     while (1);
// }

/* Build a fake interrupt frame. The form of the fake interrupt stack 
    on the Cortex-M should look like the following after it is built :
    
    Stack top:   n = STACK_SIZE - 1
        1                   .
        .                   .
        .                   .
        .                   .
        n - 17              R4
        n - 16              R5
        n - 14              R6
        n - 13              R7
        n - 12              R8
        n - 11              R9
        n - 10              R10
        n - 9               R11
        n - 8               LR
        n - 7               R0
        n - 6               R1
        n - 5               R2
        n - 4               R3
        n - 3               R12
        n - 2               lr
        n - 1               pc
        n                   xPSR
    */
uint32_t _ace_thread_create(ACE_THREAD *thread_ptr, char *name_thread, uint32_t stack_size, void (*entry_thread)(void*))
{
    uint32_t threadID = 0;
    uint32_t *stack;
    ACE_THREAD *next_thread;
    ACE_THREAD *pre_thread;
    /* Check threadID empty */
    for (threadID = 0; threadID < MAX_TASKS; threadID++)
    {
        if (ace_thread[threadID].ace_in_use == 0)
            break;
    }
    /* Determine threadID with MAX value. */
    if (threadID == MAX_TASKS)
        return -1;
    /* Allocate dynamic memory for thread stack */
    stack = (uint32_t*)malloc(stack_size* sizeof(uint32_t)); 
    
    if (stack == NULL)
    {
        return -1;
    }
    ace_thread[threadID].ace_thread_id = threadID;
    ace_thread[threadID].ace_thread_stack_start = stack;
    stack += (stack_size - 17);
    ace_thread[threadID].ace_thread_stack_ptr = stack;
    *stack++ = (uint32_t)(0);                       /* R4 */
    *stack++ = (uint32_t)(0);                       /* R5 */
    *stack++ = (uint32_t)(0);                       /* R6 */
    *stack++ = (uint32_t)(0);                       /* R7 */
    *stack++ = (uint32_t)(0);                       /* R8 */
    *stack++ = (uint32_t)(0);                       /* R9 */
    *stack++ = (uint32_t)(0);                       /* R10 */
    *stack++ = (uint32_t)(0);                       /* R11 */
    *stack++ = (uint32_t)(THREAD_PSP);              /* LR */
    *stack++ = (uint32_t)(name_thread);             /* R0 */
    *stack++ = (uint32_t)(0);                       /* R1 */
    *stack++ = (uint32_t)(0);                       /* R2 */
    *stack++ = (uint32_t)(0);                       /* R3 */
    *stack++ = (uint32_t)(0);                       /* R12 */
    *stack++ = (uint32_t) &_ace_thread_exit;        /* lr */
    *stack++ = (uint32_t)entry_thread;              /* pc */
    *stack   = (uint32_t)0x01000000;                /* xPSR */
    ace_thread[threadID].ace_thread_stack_end = stack;
    ace_thread[threadID].ace_in_use = 1;


    // thread_ptr

    if (_tx_thread_created_count == 0)
    {
        /* The created thread list is empty. Add thread to empty list. */
        _ace_thread_creatd_ptr = thread_ptr;
        thread_ptr->ace_thread_created_next = thread_ptr;
        thread_ptr->ace_thread_created_previous = thread_ptr;
    }
    else
    {
        next_thread = _ace_thread_creatd_ptr;
        pre_thread = _ace_thread_creatd_ptr->ace_thread_created_previous;

        next_thread->ace_thread_created_previous = thread_ptr;
        pre_thread->ace_thread_created_next = thread_ptr;
    }

    _tx_thread_created_count++;

    return threadID;
}

void _ace_thread_kill(uint32_t thread_id)
{
    ace_thread[thread_id].ace_in_use = 0;

    /* Free thread stack. */
    free(ace_thread[thread_id].ace_thread_stack_start);
}

void _ace_thread_exit()
{
    asm volatile ("cpsid i\n");
    _ace_thread_kill(lastTask);
    asm volatile ("cpsie i\n");

    while(1);
}


