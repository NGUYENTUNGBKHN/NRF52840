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


uint8_t ace_trace_is_init = 0;

void ace_trace_init(void)
{
    // SEGGER_RTT_Init();
    SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
    ace_trace_is_init = 1;
}


