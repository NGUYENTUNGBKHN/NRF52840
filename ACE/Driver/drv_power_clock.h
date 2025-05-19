/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_power_clock.h
    @brief      
    @date       2025/04/30
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _DRV_POWER_CLOCK_H_
#define _DRV_POWER_CLOCK_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include "drv_common.h"
#include "drv_irq.h"

__STATIC_INLINE void drv_power_clock_irq_init(void);

__STATIC_INLINE void drv_power_clock_irq_init(void)
{
    uint8_t priority = 6;

    if (!DRV_IRQ_IS_ENABLED(DRV_IRQ_NUMBER_GET(NRF_CLOCK)))
    {
        DRV_IRQ_PRIORITY_SET(DRV_IRQ_NUMBER_GET(NRF_CLOCK), priority);
        DRV_IRQ_ENABLE(DRV_IRQ_NUMBER_GET(NRF_CLOCK));
    }
}


#define drv_clock_irq_handler drv_power_clock_irq_handler


#ifdef __cplusplus
}
#endif
#endif
