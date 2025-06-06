/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_flash.c
    @brief      
    @date       2025/06/06
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#include "drv_flash.h"

static void drv_flash_word_write(uint32_t addr, uint32_t value)
{
    while (hal_nvmc_ready_check(NRF_NVMC))
    {
        /* code */
    }
    
    *(volatile uint32_t *)addr = value;
    __DMB();
}

