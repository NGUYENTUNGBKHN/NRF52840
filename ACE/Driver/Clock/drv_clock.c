/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_clock.c
    @brief      
    @date       2025/04/22
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#include "drv_clock.h"
#include "Trace/ace_trace.h"

typedef struct DRV_CLOCK_CB_S
{
    drv_clock_event_handler_t event_handler; /*!< Event handler */
    bool        drv_initialized; /*!< Driver initialized flag */
}drv_clock_cb_t;


static drv_clock_cb_t m_clock_cb;


drv_sta_t drv_clock_init(drv_clock_event_handler_t event_handler)
{
    if (m_clock_cb.drv_initialized == true)
    {
        return DRV_STA_NG;
    }

    m_clock_cb.event_handler = event_handler;
    m_clock_cb.drv_initialized = true;
    ace_trace_log("drv_clock_init\n");
    return DRV_STA_OK;
}

drv_sta_t drv_clock_enable()
{
    if (m_clock_cb.drv_initialized == false)
    {
        return DRV_STA_NG;
    }
    // NRFX_IRQ_NUMBER_GET(NRF_CLOCK); // Get IRQ number for CLOCK peripheral
    // NVIC_EnableIRQ
    ace_trace_log("drv_clock_enable %x \n",NRFX_IRQ_NUMBER_GET(NRF_CLOCK));
    return DRV_STA_OK;  
}


