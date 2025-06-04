/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_systick.h
    @brief      
    @date       2025/05/29
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _DRV_SYSTICK_H_
#define _DRV_SYSTICK_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include "drv_common.h"

/**
 * @brief The value type that holds the SysTick state.
 *
 * This variable is used to count the requested timeout.
 * @sa nrfx_systick_get
 */
typedef struct 
{
    uint32_t time; //!< Registered time value.
} drv_systick_state_t;


extern void drv_systick_init(uint32_t internal);
extern void drv_systick_delay_ms(uint32_t ms);
extern void drv_systick_delay_us(uint32_t us);

#ifdef __cplusplus
}
#endif
#endif


