/******************************************************************************/
/*! @addtogroup Group2
    @file       main.c
    @brief      
    @date       2025/06/30
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include "Trace/ace_trace.h"
#include "asm.h"
#include "hal_systick.h"

#define TASK_MAX 2
#define STACK_SIZE 256

/* Exception return behavior */
#define HANDLER_MSP	0xFFFFFFF1
#define THREAD_MSP	0xFFFFFFF9
#define THREAD_PSP	0xFFFFFFFD

void delay(uint32_t count)
{
    count *= 640000;
    volatile uint32_t i = 0;
    for (i = 0; i < count; i++)
    {
        __asm("nop");
    }
}


uint32_t *create_task(uint32_t *stack, void (*func)(void))
{
    stack += STACK_SIZE - 17;
    stack[8] = (uint32_t) THREAD_PSP;
	stack[15] = (uint32_t) func;
	stack[16] = (uint32_t) 0x01000000; /* PSR Thumb bit */
	stack = activate(stack);

	return stack;
}

void task_init()
{
    uint32_t empty[32];
    task_init_evn(empty + 32);
}

void task1()
{
    ace_trace_log("%s start \n",__func__);
    syscall();
    while (1)
    {
        /* code */
        ace_trace_log("%s OK \n",__func__);
        delay(1);
        // syscall();
    }
    
}

void task2()
{
    ace_trace_log("%s start \n",__func__);
    syscall();
    while (1)
    {
        /* code */
        ace_trace_log("%s OK \n",__func__);
        delay(1);
        // syscall();
    }
    
}

/* 64MHz */
#define CPU_CLOCK_HZ 64000000

/* 100 ms per tick. */
#define TICK_RATE_HZ 10

void systick_init()
{
    hal_systick_val_clear();
    hal_systick_load_set(CPU_CLOCK_HZ/TICK_RATE_HZ - 1);
    hal_systick_csr_set(
        HAL_SYSTICK_CSR_CLKSOURCE_CPU |
        HAL_SYSTICK_CSR_TICKINT_ENABLE |
        HAL_SYSTICK_CSR_ENABLE);
}

int main()
{
    uint32_t user_stack[TASK_MAX][STACK_SIZE];
    uint32_t *user_stack_start[TASK_MAX];

    user_stack_start[0] = &user_stack[0][0];
    user_stack_start[1] = &user_stack[1][0];
    uint8_t  current_task = 0;
    uint8_t task_count = 0;
    ace_trace_init();
    ace_trace_log("Hello!!\n");
    task_init();
    user_stack_start[0] = create_task(user_stack_start[0], &task1);
    task_count++;
    user_stack_start[1] = create_task(user_stack_start[1], &task2);
    task_count++;
    current_task = 0;
    ace_trace_log("OS start!!\n");
    systick_init();
    while (1)
    {
        user_stack_start[current_task] = activate(user_stack_start[current_task]);
        current_task = current_task == (task_count - 1) ? 0 : current_task + 1;
        // delay(10000);
        /* code */
    }
}
