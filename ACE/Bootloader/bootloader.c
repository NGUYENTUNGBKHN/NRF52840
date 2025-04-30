/******************************************************************************/
/*! @addtogroup Group2
    @file       bootloader.c
    @brief      
    @date       2025/04/28
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#include "bootloader.h"

void delay(uint32_t count)
{
    volatile uint32_t i = 0;
    for (i = 0; i < count; i++)
    {
        __asm("nop");
    }
}


void bootloader()
{
    ace_trace_log("Bootloader start\n");
    while (1)
    {
        /* code */
        // Use directly __WFE and __SEV macros since the SoftDevice is not available.

        // Wait for event.
        // __WFE();
    }
}
