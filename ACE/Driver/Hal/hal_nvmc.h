/******************************************************************************/
/*! @addtogroup Group2
    @file       hal_nvmc.h
    @brief      
    @date       2025/06/06
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _HAL_NVMC_H_
#define _HAL_NVMC_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/* CODE */
typedef enum
{
    HAL_NVMC_MODE_READONLY      = NVMC_CONFIG_WEN_Ren, ///< NVMC in read-only mode.
    HAL_NVMC_MODE_WRITE         = NVMC_CONFIG_WEN_Wen, ///< NVMC in read and write mode.
    HAL_NVMC_MODE_ERASE         = NVMC_CONFIG_WEN_Een, ///< NVMC in read and erase mode.
}hal_nvmc_mode_t;


__STATIC_INLINE bool hal_nvmc_ready_check(NRF_NVMC_Type const * p_reg)
{
    return (bool)(p_reg->READY & NVMC_READY_READY_Msk);
}

__STATIC_INLINE bool hal_nvmc_write_ready_check(NRF_NVMC_Type const * p_reg)
{
    return (bool)(p_reg->READYNEXT & NVMC_READYNEXT_READYNEXT_Msk);
}

__STATIC_INLINE void hal_nvmc_mode_set(NRF_NVMC_Type * p_reg,
                                       hal_nvmc_mode_t mode)
{
    p_reg->CONFIG = (uint32_t)mode;
}

__STATIC_INLINE void hal_nvmc_page_erase_start(NRF_NVMC_Type * p_reg,
                                               uint32_t        page_addr)
{
    p_reg->ERASEPAGE = page_addr;
}

__STATIC_INLINE void hal_nvmc_erase_all_start(NRF_NVMC_Type * p_reg)
{
    p_reg->ERASEALL = 1;
}

extern void hal_nvmc_write_byte(uint32_t address, uint8_t value);
extern void hal_nvmc_page_erase(uint32_t address);

#ifdef __cplusplus
}
#endif
#endif
