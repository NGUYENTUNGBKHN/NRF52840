/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_clock.h
    @brief      
    @date       2025/04/22
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#ifndef _DRV_CLOCK_H_
#define _DRV_CLOCK_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include "drv_common.h"

/** @brief Clock events. */
typedef enum
{
    DRV_CLOCK_EVT_HFCLK_STARTED, ///< HFCLK has been started.
    DRV_CLOCK_EVT_LFCLK_STARTED, ///< LFCLK has been started.
    DRV_CLOCK_EVT_CTTO,          ///< Calibration timeout.
    DRV_CLOCK_EVT_CAL_DONE       ///< Calibration has been done.
} drv_clock_evt_type_t;

/**
 * @brief Clock event handler.
 *
 * @param[in] event Event.
 */
typedef void (*drv_clock_event_handler_t)(drv_clock_evt_type_t event);


extern drv_sta_t drv_clock_init(drv_clock_event_handler_t event_handler);

extern drv_sta_t drv_clock_enable();

extern void drv_clock_lfclk_start(void);
extern drv_sta_t drv_clock_radio_enable();


#ifdef __cplusplus
}
#endif
#endif
