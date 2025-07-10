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
#include "hal_systick.h"
#include "ace_api.h"

#define STACK_SIZE 256

ACE_THREAD task1;
ACE_THREAD task2;
ACE_THREAD task3;

void delay(uint32_t count)
{
    count *= 640000;
    volatile uint32_t i = 0;
    for (i = 0; i < count; i++)
    {
        __asm("nop");
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

static void busy_loop(uint32_t id)
{
	while (1) {
		ace_trace_log("--> Task %d Running...\n",id);
        delay(1);
	}
}

void test1(uint32_t userdata)
{
	busy_loop(userdata);
}

void test2(uint32_t userdata)
{
	busy_loop(userdata);
}

void test3(uint32_t userdata)
{
	busy_loop(userdata);
}


int main()
{
    ace_trace_init();
    ace_trace_log("Hello %lu !!\n",sizeof(ACE_THREAD));
    const char *str1 = "Task1", *str2 = "Task2", *str3 = "Task3";

	if (_ace_thread_create(&task1, (void *) str1, STACK_SIZE, test1) == -1)
		ace_trace_log("Thread 1 creation failed\r\n");

	if (_ace_thread_create(&task2, (void *) str2, STACK_SIZE, test2) == -1)
		ace_trace_log("Thread 2 creation failed\r\n");

	if (_ace_thread_create(&task3, (void *) str3, STACK_SIZE, test3) == -1)
		ace_trace_log("Thread 3 creation failed\r\n");
    systick_init();
    _ace_initialize_kernel_enter();
    while (1)
    {

    }
}
