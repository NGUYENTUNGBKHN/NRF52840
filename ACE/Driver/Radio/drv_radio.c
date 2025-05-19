/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_radio.c
    @brief      
    @date       2025/05/13
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#include "drv_radio.h"
#include "drv_clock.h"
#include "Trace/ace_trace.h"

extern drv_radio_cb_t m_radio_cb;

drv_sta_t drv_radio_init(drv_radio_event_handler_t event_handler)
{
    if (m_radio_cb.drv_initialized == true)
    {
        return DRV_STA_NG;
    }

    

    m_radio_cb.event_handler = event_handler;
    m_radio_cb.drv_initialized = true;
    ace_trace_log("drv_radio_init\n");
    return DRV_STA_OK;
}
