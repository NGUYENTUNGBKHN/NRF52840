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
#include "drv_power_clock.h"
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

    nrfx_power_clock_irq_init();
    hal_clock_lf_src_set(HAL_CLOCK_LFCLK_SYNTH);

    return DRV_STA_OK;  
}

void drv_clock_lfclk_start(void)
{
    // NRFX_ASSERT(m_clock_cb.module_initialized);
    hal_clock_event_clear(HAL_CLOCK_EVENT_LFCLKSTARTED);
    hal_clock_interrupt_enable(HAL_CLOCK_INT_LFCLKSTARTED_MASK);

    hal_clock_task_trigger(HAL_CLOCK_TASK_LFCLKSTART);
    ace_trace_log("%s\n", __func__);
}

drv_sta_t drv_clock_irq_handler()
{
    if (m_clock_cb.event_handler == NULL)
    {
        return DRV_STA_NG;
    }
    /* High frequency clock started event */
    if (hal_clock_event_check(HAL_CLOCK_EVENT_HFCLKSTARTED))
    {
        m_clock_cb.event_handler(DRV_CLOCK_EVT_HFCLK_STARTED);
        hal_clock_event_clear(HAL_CLOCK_EVENT_HFCLKSTARTED);
    }

    if (hal_clock_event_check(HAL_CLOCK_EVENT_LFCLKSTARTED))
    {
        m_clock_cb.event_handler(DRV_CLOCK_EVT_LFCLK_STARTED);
        hal_clock_event_clear(HAL_CLOCK_EVENT_LFCLKSTARTED);
    }

    if (hal_clock_event_check(HAL_CLOCK_EVENT_CTTO))
    {
        m_clock_cb.event_handler(DRV_CLOCK_EVT_CTTO);
        hal_clock_event_clear(HAL_CLOCK_EVENT_CTTO);
    }

    if (hal_clock_event_check(HAL_CLOCK_EVENT_DONE))
    {
        m_clock_cb.event_handler(DRV_CLOCK_EVT_CAL_DONE);
        hal_clock_event_clear(HAL_CLOCK_EVENT_DONE);
    }

    return DRV_STA_OK;
}
