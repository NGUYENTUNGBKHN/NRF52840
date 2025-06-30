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



void usertask()
{
    ace_trace_log("%s-1!!\n",__func__);
    syscall();
    ace_trace_log("%s-2!!\n",__func__);
    syscall();
    while (1)
    {
        /* code */
    }
    
}


int main()
{
    uint32_t usertask_stack[256];
    uint32_t *usertask_stack_start = usertask_stack + 256 - 16;
    usertask_stack_start[8] = (unsigned int) &usertask;
    ace_trace_init();
    ace_trace_log("Hello!!\n");

    usertask_stack_start = activate(usertask_stack_start);
    ace_trace_log("come back main 1\n");
    usertask_stack_start = activate(usertask_stack_start);
    ace_trace_log("come back main 2\n");

    while (1)
    {
        /* code */
    }
}
