/******************************************************************************/
/*! @addtogroup Group2
    @file       hal_nvmc.c
    @brief      
    @date       2025/06/06
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#include "hal_nvmc.h"


static inline void wait_for_flash_ready(void)
{
    while (NRF_NVMC->READY == NVMC_READY_READY_Busy) {;}
}

void hal_nvmc_page_erase(uint32_t address)
{
    // Enable erase.
    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Een;
    __ISB();
    __DSB();

    // Erase the page
    NRF_NVMC->ERASEPAGE = address;
    wait_for_flash_ready();

    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
    __ISB();
    __DSB();
}


void hal_nvmc_write_byte(uint32_t address, uint8_t value)
{
    uint32_t byte_shift = address & (uint32_t)0x03;
    uint32_t address32 = address & ~byte_shift; // Address to the word this byte is in.
    uint32_t value32 = (*(uint32_t*)address32 & ~((uint32_t)0xFF << (byte_shift << (uint32_t)3)));
    value32 = value32 + ((uint32_t)value << (byte_shift << 3));

    // Enable write.
    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos);
    __ISB();
    __DSB();

    *(uint32_t*)address32 = value32;
    wait_for_flash_ready();

    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos);
    __ISB();
    __DSB();
}

void hal_nvmc_write_word(uint32_t address, uint32_t value)
{
    // Enable write.
    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
    __ISB();
    __DSB();

    *(uint32_t*)address = value;
    wait_for_flash_ready();

    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
    __ISB();
    __DSB();
}

void hal_nvmc_write_bytes(uint32_t address, const uint8_t * src, uint32_t num_bytes)
{
    uint32_t i;
    for (i = 0; i < num_bytes; i++)
    {
       hal_nvmc_write_byte(address + i,src[i]);
    }
}

void hal_nvmc_write_words(uint32_t address, const uint32_t * src, uint32_t num_words)
{
    uint32_t i;

    // Enable write.
    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
    __ISB();
    __DSB();

    for (i = 0; i < num_words; i++)
    {
        ((uint32_t*)address)[i] = src[i];
        wait_for_flash_ready();
    }

    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
    __ISB();
    __DSB();
}


