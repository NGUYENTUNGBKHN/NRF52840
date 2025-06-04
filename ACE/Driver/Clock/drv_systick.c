/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_systick.c
    @brief      
    @date       2025/05/29
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#include "drv_systick.h"
#include "hal_clock.h"
#include "Trace/ace_trace.h"

#define __SYSTEM_CLOCK_64M      (64000000UL)

/**
 * @brief Maximum number of ticks to delay
 *
 * The maximum number of ticks should be much lower than
 * Physical maximum count of the SysTick timer.
 * It is dictated by the fact that it would be impossible to detect delay
 * properly when the timer value warps around the starting point.
 */
#define DRV_SYSTICK_TICKS_MAX (HAL_SYSTICK_VAL_MASK / 2UL)


/**
 * @brief Number of milliseconds to wait in single loop
 *
 * Constant used by @ref nrd_drv_systick_delay_ms function
 * to split waiting into loops and rest.
 *
 * It describes the number of milliseconds to wait in single loop.
 *
 * See @ref nrfx_systick_delay_ms source code for details.
 */
#define DRV_SYSTICK_MS_STEP (64U)

/**
 * @brief Number of milliseconds in a second
 */
#define DRV_SYSTICK_MS (1000UL)

/**
 * @brief Number of microseconds in a second
 */
#define DRV_SYSTICK_US (1000UL * DRV_SYSTICK_MS)


uint32_t SystemCoreClock __attribute__((used)) = __SYSTEM_CLOCK_64M;

static inline void drv_systick_coreClock_update()
{
    SystemCoreClock = __SYSTEM_CLOCK_64M;
}
/*
 *
 * Function converts from microseconds to CPU ticks.
 *
 * @param us Number of microseconds
 *
 * @return Number of ticks
 *
 * @sa nrfx_systick_ms_tick
 */
static inline uint32_t drv_systick_us_tick(uint32_t us)
{
    return us * ((SystemCoreClock) / DRV_SYSTICK_US);
}

static inline uint32_t drv_systick_ms_tick(uint32_t ms)
{
    return ms * ((SystemCoreClock) / DRV_SYSTICK_MS);
}


void drv_systick_init(uint32_t internal)
{
    hal_clock_event_clear(HAL_CLOCK_EVENT_HFCLKSTARTED);
    hal_clock_task_trigger(HAL_CLOCK_TASK_HFCLKSTART);
    while(!hal_clock_event_check(HAL_CLOCK_EVENT_HFCLKSTARTED)){}

    hal_systick_val_clear();
    hal_systick_load_set(internal - 1);
    hal_systick_csr_set(
        HAL_SYSTICK_CSR_CLKSOURCE_CPU |
        HAL_SYSTICK_CSR_TICKINT_ENABLE |
        HAL_SYSTICK_CSR_ENABLE);
}

void drv_systick_get(drv_systick_state_t * p_state)
{
    p_state->time = hal_systick_val_get();
}

bool drv_systick_test(drv_systick_state_t const * p_state, uint32_t us)
{
    // NRFX_SYSTICK_ASSERT_TIMEOUT(us);

    const uint32_t diff = HAL_SYSTICK_VAL_MASK & ((p_state->time) - hal_systick_val_get());
    return (diff >= drv_systick_us_tick(us));
}

void drv_systick_delay_ticks(uint32_t ticks)
{
    // NRFX_ASSERT(ticks <= DRV_SYSTICK_TICKS_MAX);

    const uint32_t start = hal_systick_val_get();
    while ((HAL_SYSTICK_VAL_MASK & (start - hal_systick_val_get())) < ticks)
    {
        /* Nothing to do */
    }
}

void drv_systick_delay_us(uint32_t us)
{
    // NRFX_SYSTICK_ASSERT_TIMEOUT(us);
    drv_systick_delay_ticks(drv_systick_us_tick(us));
}

void drv_systick_delay_ms(uint32_t ms)
{
    uint32_t n = ms / DRV_SYSTICK_MS_STEP;
    uint32_t r = ms % DRV_SYSTICK_MS_STEP;
    while (0 != (n--))
    {
        drv_systick_delay_ticks(drv_systick_ms_tick(DRV_SYSTICK_MS_STEP));
    }
    drv_systick_delay_ticks(drv_systick_ms_tick(r));
}
volatile static uint32_t count = 0;

void drv_systick_handler()
{
    count++;
    //ace_trace_log("systick\n");
}

