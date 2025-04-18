/******************************************************************************/
/*! @addtogroup Group2
    @file       ace_trace.c
    @brief      
    @date       2025/04/11
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#include "Trace/ace_trace.h"
#include <stdio.h>
#include <stdarg.h>



extern int SEGGER_RTT_vprintf(unsigned BufferIndex, const char * sFormat, va_list * pParamList);

static uint8_t ace_trace_is_init = 1;

__attribute__((section(".ram_code")))
void ace_trace_init(void)
{
    SEGGER_RTT_Init();
    SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);
    ace_trace_is_init = 1;
}

int ace_trace_log(const char *format, ...)
{
    // if (ace_trace_is_init == 0)
    // {
    //     return -1;
    // }
    
    int r;
    va_list ParamList;

    va_start(ParamList, format);
    r = SEGGER_RTT_vprintf(0, format, &ParamList);
    va_end(ParamList);
    return r;
}