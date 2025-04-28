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

#define NRFX_PERIPHERAL_ID_GET(base_addr)  (uint8_t)((uint32_t)(base_addr) >> 12)

#define NRFX_IRQ_NUMBER_GET(base_addr)  NRFX_PERIPHERAL_ID_GET(base_addr)

/* CODE */
#include "hal_clock.h"

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


