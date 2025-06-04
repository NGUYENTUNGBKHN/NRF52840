/******************************************************************************/
/*! @addtogroup Group2
    @file       hal_systick.h
    @brief      
    @date       2025/05/29
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _HAL_SYSTICK_H_
#define _HAL_SYSTICK_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include "hal_common.h"


#define HAL_SYSTICK_VAL_MASK    SysTick_VAL_CURRENT_Msk

typedef enum
{
    HAL_SYSTICK_CSR_COUNTFLAG_MASK  = SysTick_CTRL_COUNTFLAG_Msk,       /**< Status flag: Returns 1 if timer counted to 0 since the last read of this register. */

    HAL_SYSTICK_CSR_CLKSOURCE_MASK  = SysTick_CTRL_CLKSOURCE_Msk,       /**< Configuration bit: Select the SysTick clock source. */
    HAL_SYSTICK_CSR_CLKSOURCE_REF   = 0U << SysTick_CTRL_CLKSOURCE_Pos, /**< Configuration value: Select reference clock. */
    HAL_SYSTICK_CSR_CLKSOURCE_CPU   = 1U << SysTick_CTRL_CLKSOURCE_Pos, /**< Configuration value: Select CPU clock. */

    HAL_SYSTICK_CSR_TICKINT_MASK    = SysTick_CTRL_TICKINT_Msk,         /**< Configuration bit: Enables SysTick exception request. */
    HAL_SYSTICK_CSR_TICKINT_ENABLE  = 1U << SysTick_CTRL_TICKINT_Pos,   /**< Configuration value: Counting down to zero does not assert the SysTick exception request. */
    HAL_SYSTICK_CSR_TICKINT_DISABLE = 0U << SysTick_CTRL_TICKINT_Pos,   /**< Configuration value: Counting down to zero to asserts the SysTick exception request. */

    HAL_SYSTICK_CSR_ENABLE_MASK     = SysTick_CTRL_ENABLE_Msk,          /**< Configuration bit: Enable the SysTick timer. */
    HAL_SYSTICK_CSR_ENABLE          = 1U << SysTick_CTRL_ENABLE_Pos,    /**< Configuration value: Counter enabled. */
    HAL_SYSTICK_CSR_DISABLE         = 0U << SysTick_CTRL_ENABLE_Pos     /**< Configuration value: Counter disabled. */
}hal_systick_csr_flags_t;

__STATIC_INLINE uint32_t hal_systick_csr_get(void)
{
    return SysTick->CTRL;
}

__STATIC_INLINE void hal_systick_csr_set(uint32_t val)
{
    SysTick->CTRL = val;
}

__STATIC_INLINE uint32_t hal_systick_load_get(void)
{
    return SysTick->LOAD;
}

__STATIC_INLINE void hal_systick_load_set(uint32_t val)
{
    SysTick->LOAD = val;
}

__STATIC_INLINE uint32_t hal_systick_val_get(void)
{
    return SysTick->VAL;
}

__STATIC_INLINE void hal_systick_val_clear(void)
{
    SysTick->VAL = 0;
}

__STATIC_INLINE uint32_t hal_systick_calib_get(void)
{
    return SysTick->CALIB;
}

#ifdef __cplusplus
}
#endif
#endif
