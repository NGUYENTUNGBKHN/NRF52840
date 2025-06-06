/******************************************************************************/
/*! @addtogroup Group2
    @file       hal_timer.h
    @brief      
    @date       2025/06/06
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _HAL_TIMER_H_
#define _HAL_TIMER_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include "hal_common.h"

/** @brief Timer tasks. */
typedef enum
{
    HAL_TIMER_TASK_START    = offsetof(NRF_TIMER_Type, TASKS_START),      ///< Task for starting the timer.
    HAL_TIMER_TASK_STOP     = offsetof(NRF_TIMER_Type, TASKS_STOP),       ///< Task for stopping the timer.
    HAL_TIMER_TASK_COUNT    = offsetof(NRF_TIMER_Type, TASKS_COUNT),      ///< Task for incrementing the timer (in counter mode).
    HAL_TIMER_TASK_CLEAR    = offsetof(NRF_TIMER_Type, TASKS_CLEAR),      ///< Task for resetting the timer value.
    HAL_TIMER_TASK_SHUTDOWN = offsetof(NRF_TIMER_Type, TASKS_SHUTDOWN),   ///< Task for powering off the timer.
    HAL_TIMER_TASK_CAPTURE0 = offsetof(NRF_TIMER_Type, TASKS_CAPTURE[0]), ///< Task for capturing the timer value on channel 0.
    HAL_TIMER_TASK_CAPTURE1 = offsetof(NRF_TIMER_Type, TASKS_CAPTURE[1]), ///< Task for capturing the timer value on channel 1.
    HAL_TIMER_TASK_CAPTURE2 = offsetof(NRF_TIMER_Type, TASKS_CAPTURE[2]), ///< Task for capturing the timer value on channel 2.
    HAL_TIMER_TASK_CAPTURE3 = offsetof(NRF_TIMER_Type, TASKS_CAPTURE[3]), ///< Task for capturing the timer value on channel 3.
    HAL_TIMER_TASK_CAPTURE4 = offsetof(NRF_TIMER_Type, TASKS_CAPTURE[4]), ///< Task for capturing the timer value on channel 4.
    HAL_TIMER_TASK_CAPTURE5 = offsetof(NRF_TIMER_Type, TASKS_CAPTURE[5]), ///< Task for capturing the timer value on channel 5.
} hal_timer_task_t;


/** @brief Timer events. */
typedef enum
{
    HAL_TIMER_EVENT_COMPARE0 = offsetof(NRF_TIMER_Type, EVENTS_COMPARE[0]), ///< Event from compare channel 0.
    HAL_TIMER_EVENT_COMPARE1 = offsetof(NRF_TIMER_Type, EVENTS_COMPARE[1]), ///< Event from compare channel 1.
    HAL_TIMER_EVENT_COMPARE2 = offsetof(NRF_TIMER_Type, EVENTS_COMPARE[2]), ///< Event from compare channel 2.
    HAL_TIMER_EVENT_COMPARE3 = offsetof(NRF_TIMER_Type, EVENTS_COMPARE[3]), ///< Event from compare channel 3.
    HAL_TIMER_EVENT_COMPARE4 = offsetof(NRF_TIMER_Type, EVENTS_COMPARE[4]), ///< Event from compare channel 4.
    HAL_TIMER_EVENT_COMPARE5 = offsetof(NRF_TIMER_Type, EVENTS_COMPARE[5]), ///< Event from compare channel 5.
} hal_timer_event_t;

/** @brief Types of timer shortcuts. */
typedef enum
{
    HAL_TIMER_SHORT_COMPARE0_STOP_MASK = TIMER_SHORTS_COMPARE0_STOP_Msk,   ///< Shortcut for stopping the timer based on compare 0.
    HAL_TIMER_SHORT_COMPARE1_STOP_MASK = TIMER_SHORTS_COMPARE1_STOP_Msk,   ///< Shortcut for stopping the timer based on compare 1.
    HAL_TIMER_SHORT_COMPARE2_STOP_MASK = TIMER_SHORTS_COMPARE2_STOP_Msk,   ///< Shortcut for stopping the timer based on compare 2.
    HAL_TIMER_SHORT_COMPARE3_STOP_MASK = TIMER_SHORTS_COMPARE3_STOP_Msk,   ///< Shortcut for stopping the timer based on compare 3.
    HAL_TIMER_SHORT_COMPARE4_STOP_MASK = TIMER_SHORTS_COMPARE4_STOP_Msk,   ///< Shortcut for stopping the timer based on compare 4.
    HAL_TIMER_SHORT_COMPARE5_STOP_MASK = TIMER_SHORTS_COMPARE5_STOP_Msk,   ///< Shortcut for stopping the timer based on compare 5.
    HAL_TIMER_SHORT_COMPARE0_CLEAR_MASK = TIMER_SHORTS_COMPARE0_CLEAR_Msk, ///< Shortcut for clearing the timer based on compare 0.
    HAL_TIMER_SHORT_COMPARE1_CLEAR_MASK = TIMER_SHORTS_COMPARE1_CLEAR_Msk, ///< Shortcut for clearing the timer based on compare 1.
    HAL_TIMER_SHORT_COMPARE2_CLEAR_MASK = TIMER_SHORTS_COMPARE2_CLEAR_Msk, ///< Shortcut for clearing the timer based on compare 2.
    HAL_TIMER_SHORT_COMPARE3_CLEAR_MASK = TIMER_SHORTS_COMPARE3_CLEAR_Msk, ///< Shortcut for clearing the timer based on compare 3.
    HAL_TIMER_SHORT_COMPARE4_CLEAR_MASK = TIMER_SHORTS_COMPARE4_CLEAR_Msk, ///< Shortcut for clearing the timer based on compare 4.
    HAL_TIMER_SHORT_COMPARE5_CLEAR_MASK = TIMER_SHORTS_COMPARE5_CLEAR_Msk, ///< Shortcut for clearing the timer based on compare 5.
} hal_timer_short_mask_t;

/** @brief Timer modes. */
typedef enum
{
    HAL_TIMER_MODE_TIMER             = TIMER_MODE_MODE_Timer,           ///< Timer mode: timer.
    HAL_TIMER_MODE_COUNTER           = TIMER_MODE_MODE_Counter,         ///< Timer mode: counter.
    HAL_TIMER_MODE_LOW_POWER_COUNTER = TIMER_MODE_MODE_LowPowerCounter, ///< Timer mode: low-power counter.
} hal_timer_mode_t;

/** @brief Timer bit width. */
typedef enum
{
    HAL_TIMER_BIT_WIDTH_8  = TIMER_BITMODE_BITMODE_08Bit, ///< Timer bit width 8 bit.
    HAL_TIMER_BIT_WIDTH_16 = TIMER_BITMODE_BITMODE_16Bit, ///< Timer bit width 16 bit.
    HAL_TIMER_BIT_WIDTH_24 = TIMER_BITMODE_BITMODE_24Bit, ///< Timer bit width 24 bit.
    HAL_TIMER_BIT_WIDTH_32 = TIMER_BITMODE_BITMODE_32Bit  ///< Timer bit width 32 bit.
} hal_timer_bit_width_t;

/** @brief Timer prescalers. */
typedef enum
{
    HAL_TIMER_FREQ_16MHz = 0, ///< Timer frequency 16 MHz.
    HAL_TIMER_FREQ_8MHz,      ///< Timer frequency 8 MHz.
    HAL_TIMER_FREQ_4MHz,      ///< Timer frequency 4 MHz.
    HAL_TIMER_FREQ_2MHz,      ///< Timer frequency 2 MHz.
    HAL_TIMER_FREQ_1MHz,      ///< Timer frequency 1 MHz.
    HAL_TIMER_FREQ_500kHz,    ///< Timer frequency 500 kHz.
    HAL_TIMER_FREQ_250kHz,    ///< Timer frequency 250 kHz.
    HAL_TIMER_FREQ_125kHz,    ///< Timer frequency 125 kHz.
    HAL_TIMER_FREQ_62500Hz,   ///< Timer frequency 62500 Hz.
    HAL_TIMER_FREQ_31250Hz    ///< Timer frequency 31250 Hz.
} hal_timer_frequency_t;

/** @brief Timer capture/compare channels. */
typedef enum
{
    HAL_TIMER_CC_CHANNEL0 = 0, ///< Timer capture/compare channel 0.
    HAL_TIMER_CC_CHANNEL1,     ///< Timer capture/compare channel 1.
    HAL_TIMER_CC_CHANNEL2,     ///< Timer capture/compare channel 2.
    HAL_TIMER_CC_CHANNEL3,     ///< Timer capture/compare channel 3.
    HAL_TIMER_CC_CHANNEL4,     ///< Timer capture/compare channel 4.
    HAL_TIMER_CC_CHANNEL5,     ///< Timer capture/compare channel 5.
} hal_timer_cc_channel_t;

/** @brief Timer interrupts. */
typedef enum
{
    HAL_TIMER_INT_COMPARE0_MASK = TIMER_INTENSET_COMPARE0_Msk, ///< Timer interrupt from compare event on channel 0.
    HAL_TIMER_INT_COMPARE1_MASK = TIMER_INTENSET_COMPARE1_Msk, ///< Timer interrupt from compare event on channel 1.
    HAL_TIMER_INT_COMPARE2_MASK = TIMER_INTENSET_COMPARE2_Msk, ///< Timer interrupt from compare event on channel 2.
    HAL_TIMER_INT_COMPARE3_MASK = TIMER_INTENSET_COMPARE3_Msk, ///< Timer interrupt from compare event on channel 3.
    HAL_TIMER_INT_COMPARE4_MASK = TIMER_INTENSET_COMPARE4_Msk, ///< Timer interrupt from compare event on channel 4.
    HAL_TIMER_INT_COMPARE5_MASK = TIMER_INTENSET_COMPARE5_Msk, ///< Timer interrupt from compare event on channel 5.
} hal_timer_int_mask_t;

/* Task */
__STATIC_INLINE void hal_timer_task_trigger(NRF_TIMER_Type * p_reg,
                                            hal_timer_task_t task)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)task)) = 0x1UL;
}

__STATIC_INLINE uint32_t * hal_timer_task_address_get(NRF_TIMER_Type * p_reg,
                                                      hal_timer_task_t task)
{
    return (uint32_t *)((uint8_t *)p_reg + (uint32_t)task);
}

/* Event */
__STATIC_INLINE void hal_timer_event_clear(NRF_TIMER_Type * p_reg,
                                           hal_timer_event_t event)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event)) = 0x0UL;
}

__STATIC_INLINE bool hal_timer_event_check(NRF_TIMER_Type * p_reg,
                                           hal_timer_event_t event)
{
    return (bool)*(volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event);
}

__STATIC_INLINE uint32_t * hal_timer_event_address_get(NRF_TIMER_Type * p_reg,
                                                       hal_timer_event_t event)
{
    return (uint32_t *)((uint8_t *)p_reg + (uint32_t)event);
}

/* SHort */
__STATIC_INLINE void hal_timer_shorts_enable(NRF_TIMER_Type * p_reg,
                                             uint32_t mask)
{
    p_reg->SHORTS |= mask;
}

__STATIC_INLINE void hal_timer_shorts_disable(NRF_TIMER_Type * p_reg,
                                              uint32_t mask)
{
    p_reg->SHORTS &= ~(mask);
}

/* Interrupt */
__STATIC_INLINE void hal_timer_int_enable(NRF_TIMER_Type * p_reg,
                                          uint32_t mask)
{
    p_reg->INTENSET = mask;
}

__STATIC_INLINE void hal_timer_int_disable(NRF_TIMER_Type * p_reg,
                                           uint32_t mask)
{
    p_reg->INTENCLR = mask;
}

__STATIC_INLINE bool hal_timer_int_enable_check(NRF_TIMER_Type * p_reg,
                                                uint32_t timer_int)
{
    return (bool)(p_reg->INTENSET & timer_int);
}

/* MODE */
__STATIC_INLINE void hal_timer_mode_set(NRF_TIMER_Type * p_reg,
                                        hal_timer_mode_t mode)
{
    p_reg->MODE = (p_reg->MODE & ~TIMER_MODE_MODE_Msk) |
                    ((mode << TIMER_MODE_MODE_Pos) & TIMER_MODE_MODE_Msk);
}

__STATIC_INLINE hal_timer_mode_t nrf_timer_mode_get(NRF_TIMER_Type * p_reg)
{
    return (hal_timer_mode_t)(p_reg->MODE);
}

/* BIT MODE */
__STATIC_INLINE void hal_timer_bit_width_set(NRF_TIMER_Type * p_reg,
                                             hal_timer_bit_width_t bit_width)
{
    p_reg->BITMODE = (p_reg->BITMODE & ~TIMER_BITMODE_BITMODE_Msk) |
                       ((bit_width << TIMER_BITMODE_BITMODE_Pos) &
                            TIMER_BITMODE_BITMODE_Msk);
}

__STATIC_INLINE hal_timer_bit_width_t nrf_timer_bit_width_get(NRF_TIMER_Type * p_reg)
{
    return (hal_timer_bit_width_t)(p_reg->BITMODE);
}

/* Frequency */
__STATIC_INLINE void hal_timer_frequency_set(NRF_TIMER_Type * p_reg,
                                             hal_timer_frequency_t frequency)
{
    p_reg->PRESCALER = (p_reg->PRESCALER & ~TIMER_PRESCALER_PRESCALER_Msk) |
                         ((frequency << TIMER_PRESCALER_PRESCALER_Pos) &
                              TIMER_PRESCALER_PRESCALER_Msk);
}

__STATIC_INLINE hal_timer_frequency_t nrf_timer_frequency_get(NRF_TIMER_Type * p_reg)
{
    return (hal_timer_frequency_t)(p_reg->PRESCALER);
}

/* Compare/Counter */
__STATIC_INLINE void hal_timer_cc_write(NRF_TIMER_Type * p_reg,
                                        hal_timer_cc_channel_t cc_channel,
                                        uint32_t               cc_value)
{
    p_reg->CC[cc_channel] = cc_value;
}

__STATIC_INLINE uint32_t hal_timer_cc_read(NRF_TIMER_Type * p_reg,
                                           hal_timer_cc_channel_t cc_channel)
{
    return (uint32_t)p_reg->CC[cc_channel];
}

__STATIC_INLINE hal_timer_task_t hal_timer_capture_task_get(uint32_t channel)
{
    return (hal_timer_task_t)HAL_OFFSETOF(NRF_TIMER_Type, TASKS_CAPTURE[channel]);
}

__STATIC_INLINE hal_timer_event_t hal_timer_compare_event_get(uint32_t channel)
{
    return (hal_timer_event_t)HAL_OFFSETOF(NRF_TIMER_Type, EVENTS_COMPARE[channel]);
}

__STATIC_INLINE hal_timer_int_mask_t hal_timer_compare_int_get(uint32_t channel)
{
    return (hal_timer_int_mask_t)
        ((uint32_t)HAL_TIMER_INT_COMPARE0_MASK << channel);
}

__STATIC_INLINE uint32_t hal_timer_us_to_ticks(uint32_t              time_us,
                                               hal_timer_frequency_t frequency)
{
    // The "frequency" parameter here is actually the prescaler value, and the
    // timer runs at the following frequency: f = 16 MHz / 2^prescaler.
    uint32_t prescaler = (uint32_t)frequency;
    uint64_t ticks = ((time_us * 16ULL) >> prescaler);
    // NRFX_ASSERT(ticks <= UINT32_MAX);
    return (uint32_t)ticks;
}

__STATIC_INLINE uint32_t hal_timer_ms_to_ticks(uint32_t              time_ms,
                                               hal_timer_frequency_t frequency)
{
    // The "frequency" parameter here is actually the prescaler value, and the
    // timer runs at the following frequency: f = 16000 kHz / 2^prescaler.
    uint32_t prescaler = (uint32_t)frequency;
    uint64_t ticks = ((time_ms * 16000ULL) >> prescaler);
    // NRFX_ASSERT(ticks <= UINT32_MAX);
    return (uint32_t)ticks;
}
#ifdef __cplusplus
}
#endif
#endif
