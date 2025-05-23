/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_common.h
    @brief      
    @date       2025/04/16
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#ifndef _DRV_COMMON_H_
#define _DRV_COMMON_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include "stdbool.h"
#include "nrf52840.h"
#include "hal_uart.h"
#include "hal_uarte.h"
#include "hal_clock.h"
#include "hal_radio.h"

#define DRV_PERIPHERAL_ID_GET(base_addr)  (uint8_t)((uint32_t)(base_addr) >> 12)

#define DRV_IRQ_NUMBER_GET(base_addr)  DRV_PERIPHERAL_ID_GET(base_addr)

/**
 * @brief Macro for setting the priority of a specific IRQ.
 *
 * @param irq_number  IRQ number.
 * @param priority    Priority to set.
 */
#define DRV_IRQ_PRIORITY_SET(irq_number, priority) \
    _DRV_IRQ_PRIORITY_SET(irq_number, priority)
static inline void _DRV_IRQ_PRIORITY_SET(IRQn_Type irq_number,
                                          uint8_t   priority)
{
    // ASSERT(INTERRUPT_PRIORITY_IS_VALID(priority));
    NVIC_SetPriority(irq_number, priority);
}

/**
 * @brief Macro for enabling a specific IRQ.
 *
 * @param irq_number  IRQ number.
 */
#define DRV_IRQ_ENABLE(irq_number)  _DRV_IRQ_ENABLE(irq_number)
static inline void _DRV_IRQ_ENABLE(IRQn_Type irq_number)
{
    NVIC_EnableIRQ(irq_number);
}

/**
 * @brief Macro for disabling a specific IRQ.
 *
 * @param irq_number  IRQ number.
 */
#define DRV_IRQ_DISABLE(irq_number)  _DRV_IRQ_DISABLE(irq_number)
static inline void _DRV_IRQ_DISABLE(IRQn_Type irq_number)
{
    NVIC_DisableIRQ(irq_number);
}

/**
 * @brief Macro for checking if a specific IRQ is enabled.
 *
 * @param irq_number  IRQ number.
 *
 * @retval true  If the IRQ is enabled.
 * @retval false Otherwise.
 */
#define DRV_IRQ_IS_ENABLED(irq_number)  _DRV_IRQ_IS_ENABLED(irq_number)
static inline bool _DRV_IRQ_IS_ENABLED(IRQn_Type irq_number)
{
    return 0 != (NVIC->ISER[irq_number / 32] & (1UL << (irq_number % 32)));
}




typedef enum DRV_STA_s
{
    DRV_STA_OK = 0,     /* 0x00 : No error */        
    DRV_STA_NG = -1,    /* 0xFF : Error  */
}drv_sta_t;


// __STATIC_INLINE IRQn_Type drv_get_irq_number(void const * p_reg)
// {
//     return (IRQn_Type)NRFX_IRQ_NUMBER_GET(p_reg);
// }

#ifdef __cplusplus
}
#endif
#endif


