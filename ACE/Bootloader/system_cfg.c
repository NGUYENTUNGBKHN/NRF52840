/******************************************************************************/
/*! @addtogroup Group2
    @file       system_cfg.c
    @brief      
    @date       2025/06/05
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#include "nrf52840.h"
#include "nrf52840_bitfields.h"


#define RESET_PIN 18

/* -- NVMC utility functions -- */
/* Waits until NVMC is done with the current pending action */
void nvmc_wait(void)
{
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
}

/*  Configure the NVMC to "mode".
    Mode must be an enumerator of field NVMC_CONFIG_WEN */
void nvmc_config(uint32_t mode)
{
    NRF_NVMC->CONFIG = mode << NVMC_CONFIG_WEN_Pos;
    nvmc_wait();
}


void system_init()
{
    if (((NRF_UICR->PSELRESET[0] & UICR_PSELRESET_CONNECT_Msk) != (UICR_PSELRESET_CONNECT_Connected << UICR_PSELRESET_CONNECT_Pos)) ||
        ((NRF_UICR->PSELRESET[1] & UICR_PSELRESET_CONNECT_Msk) != (UICR_PSELRESET_CONNECT_Connected << UICR_PSELRESET_CONNECT_Pos)))
    {
        nvmc_config(NVMC_CONFIG_WEN_Wen);
        NRF_UICR->PSELRESET[0] = RESET_PIN;
        nvmc_wait();
        NRF_UICR->PSELRESET[1] = RESET_PIN;
        nvmc_wait();
        nvmc_config(NVMC_CONFIG_WEN_Ren);
        NVIC_SystemReset();        
    }
}
