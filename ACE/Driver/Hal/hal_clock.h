/******************************************************************************/
/*! @addtogroup Group2
    @file       hal_clock.h
    @brief      
    @date       2025/04/22
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _HAL_CLOCK_H_
#define _HAL_CLOCK_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief   Low frequency clock source.
 */
typedef enum
{
    HAL_CLOCK_LFCLK_RC = CLOCK_LFCLKSTAT_SRC_RC, /*!< LFCLK RC */
    HAL_CLOCK_LFCLK_XTAL = CLOCK_LFCLKSTAT_SRC_Xtal, /*!< LFCLK XTAL */
} hal_clock_lfclk_t;

/**
 * @brief   High frequency clock source.
 */
typedef enum
{
    HAL_CLOCK_HFCLK_LOW_ACCURACY = CLOCK_HFCLKSTAT_SRC_RC, /*!< HFCLK high accuracy */
    HAL_CLOCK_HFCLK_HIGH_ACCURACY = CLOCK_HFCLKSTAT_SRC_Xtal, /*!< HFCLK high accuracy */
} hal_clock_hfclk_t;


/**
 * @brief   Task.
 * 
 * @details Task to start/stop HFCLK and LFCLK.
 */
typedef enum
{
    HAL_CLOCK_TASK_HFCLKSTART = offsetof(NRF_CLOCK_Type, TASKS_HFCLKSTART), /*!< HFCLKSTART task */
    HAL_CLOCK_TASK_HFCLKSTOP  = offsetof(NRF_CLOCK_Type, TASKS_HFCLKSTOP),  /*!< HFCLKSTOP task */
    HAL_CLOCK_TASK_LFCLKSTART = offsetof(NRF_CLOCK_Type, TASKS_LFCLKSTART), /*!< LFCLKSTART task */
    HAL_CLOCK_TASK_LFCLKSTOP  = offsetof(NRF_CLOCK_Type, TASKS_LFCLKSTOP),  /*!< LFCLKSTOP task */
    /* Cablibration */
    HAL_CLOCK_TASK_CAL       = offsetof(NRF_CLOCK_Type, TASKS_CAL),        /*!< CAL task */
    HAL_CLOCK_TASK_CTSTART   = offsetof(NRF_CLOCK_Type, TASKS_CTSTART),    /*!< CTSTART task */
    HAL_CLOCK_TASK_CTSTOP    = offsetof(NRF_CLOCK_Type, TASKS_CTSTOP),     /*!< CTSTOP task */
} hal_clock_task_t;


/**
 * @brief   Event.
 * 
 * @details Event to indicate that HFCLK and LFCLK have started/stopped.
 */
typedef enum
{
    HAL_CLOCK_EVENT_HFCLKSTARTED = offsetof(NRF_CLOCK_Type, EVENTS_HFCLKSTARTED), /*!< HFCLKSTARTED event */
    HAL_CLOCK_EVENT_LFCLKSTARTED = offsetof(NRF_CLOCK_Type, EVENTS_LFCLKSTARTED), /*!< LFCLKSTARTED event */
    /* Calibration */
    HAL_CLOCK_EVENT_CTTO       = offsetof(NRF_CLOCK_Type, EVENTS_CTTO),        /*!< CTTO event */
    HAL_CLOCK_EVENT_DONE       = offsetof(NRF_CLOCK_Type, EVENTS_DONE),        /*!< DONE event */
    /*  */
    HAL_CLOCK_EVENT_CTSTARTED  = offsetof(NRF_CLOCK_Type, EVENTS_CTSTARTED),   /*!< CTSTARTED event */
    HAL_CLOCK_EVENT_CTSTOPPED  = offsetof(NRF_CLOCK_Type, EVENTS_CTSTOPPED),   /*!< CTSTOPPED event */
} hal_clock_event_t;


/** @brief Interrupts. */
typedef enum
{
    HAL_CLOCK_INT_HFCLKSTARTED_MASK = CLOCK_INTENSET_HFCLKSTARTED_Msk, /*!< HFCLKSTARTED event */
    HAL_CLOCK_INT_LFCLKSTARTED_MASK = CLOCK_INTENSET_LFCLKSTARTED_Msk, /*!< LFCLKSTARTED event */
    /* Calibration */
    HAL_CLOCK_INT_CTTO_MASK    = CLOCK_INTENSET_CTTO_Msk,        /*!< CTTO event */
    HAL_CLOCK_INT_DONE_MASK    = CLOCK_INTENSET_DONE_Msk,        /*!< DONE event */
    /*  */
    HAL_CLOCK_INT_CTSTARTED_MASK = CLOCK_INTENSET_CTSTARTED_Msk, /*!< CTSTARTED event */
    HAL_CLOCK_INT_CTSTOPPED_MASK = CLOCK_INTENSET_CTSTOPPED_Msk, /*!< CTSTOPPED event */
} hal_clock_int_mask_t;


/**
 * @brief   Enable clock interrupt
 * @details Enable clock interrupt
 * @param   int_mask  Interrupt mask to enable  
 * */
__STATIC_INLINE void hal_clock_interrupt_enable(uint32_t int_mask);


/**
 * @brief   Disable clock interrupt
 * @details Disable clock interrupt
 * @param   int_mask  Interrupt mask to disable  
 * */
__STATIC_INLINE void hal_clock_interrupt_disable(uint32_t int_mask);




/* CODE */
__STATIC_INLINE void hal_clock_interrupt_enable(uint32_t int_mask)
{
    NRF_CLOCK->INTENSET = int_mask;
}

__STATIC_INLINE void hal_clock_interrupt_disable(uint32_t int_mask)
{
    NRF_CLOCK->INTENCLR = int_mask;
}

__STATIC_INLINE bool hal_clock_interrupt_enable_check(hal_clock_int_mask_t int_mask)
{
    return ((uint32_t)NRF_CLOCK->INTENCLR & int_mask);
}

__STATIC_INLINE uint32_t hal_clock_task_address_get(hal_clock_task_t task)
{
    return ((uint32_t)NRF_CLOCK + task);
}

__STATIC_INLINE void hal_clock_task_trigger(hal_clock_task_t task)
{
    *(volatile uint32_t *)((uint8_t *)NRF_CLOCK + task) = 1;
}

__STATIC_INLINE uint32_t hal_clock_event_address_get(hal_clock_event_t event)
{
    return ((uint32_t)NRF_CLOCK + event);
}

__STATIC_INLINE void hal_clock_event_clear(hal_clock_event_t event)
{
    *(volatile uint32_t *)((uint8_t *)NRF_CLOCK + event) = 0;
}

__STATIC_INLINE uint32_t hal_clock_event_check(hal_clock_event_t event)
{
    return ((uint32_t)NRF_CLOCK->EVENTS_HFCLKSTARTED & event);
}

__STATIC_INLINE void hal_clock_lf_src_set(hal_clock_lfclk_t source)
{
    NRF_CLOCK->LFCLKSRC = source;
}

__STATIC_INLINE hal_clock_lfclk_t hal_clock_lf_src_get(void)
{
    return (hal_clock_lfclk_t)(NRF_CLOCK->LFCLKSRC);
}

__STATIC_INLINE bool hal_clock_lf_is_running(void)
{
    return ((NRF_CLOCK->LFCLKSTAT &
             CLOCK_LFCLKSTAT_STATE_Msk) >> CLOCK_LFCLKSTAT_STATE_Pos);
}

__STATIC_INLINE hal_clock_hfclk_t hal_clock_hf_src_get(void)
{
    return (hal_clock_hfclk_t)((NRF_CLOCK->HFCLKSTAT &
                                CLOCK_HFCLKSTAT_SRC_Msk) >> CLOCK_HFCLKSTAT_SRC_Pos);
}

__STATIC_INLINE bool hal_clock_hf_is_running(hal_clock_hfclk_t clk_src)
{
    return (NRF_CLOCK->HFCLKSTAT & (CLOCK_HFCLKSTAT_STATE_Msk | CLOCK_HFCLKSTAT_SRC_Msk)) ==
            (CLOCK_HFCLKSTAT_STATE_Msk | (clk_src << CLOCK_HFCLKSTAT_SRC_Pos));
}





#ifdef __cplusplus
}
#endif
#endif


