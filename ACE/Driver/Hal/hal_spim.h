/******************************************************************************/
/*! @addtogroup Group2
    @file       hal_spim.h
    @brief      
    @date       2025/05/29
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _HAL_SPIM_H_
#define _HAL_SPIM_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include "hal_common.h"

/**
 * @brief This value can be used as a parameter for the @ref nrf_spim_pins_set
 *        function to specify that a given SPI signal (SCK, MOSI, or MISO)
 *        shall not be connected to a physical pin.
 */
#define HAL_SPIM_PIN_NOT_CONNECTED  0xFFFFFFFF

/** @brief SPIM tasks. */
typedef enum
{
    HAL_SPIM_TASK_START   = offsetof(NRF_SPIM_Type, TASKS_START),   ///< Start SPI transaction.
    HAL_SPIM_TASK_STOP    = offsetof(NRF_SPIM_Type, TASKS_STOP),    ///< Stop SPI transaction.
    HAL_SPIM_TASK_SUSPEND = offsetof(NRF_SPIM_Type, TASKS_SUSPEND), ///< Suspend SPI transaction.
    HAL_SPIM_TASK_RESUME  = offsetof(NRF_SPIM_Type, TASKS_RESUME)   ///< Resume SPI transaction.
} hal_spim_task_t;

/** @brief SPIM events. */
typedef enum
{
    HAL_SPIM_EVENT_STOPPED = offsetof(NRF_SPIM_Type, EVENTS_STOPPED), ///< SPI transaction has stopped.
    HAL_SPIM_EVENT_ENDRX   = offsetof(NRF_SPIM_Type, EVENTS_ENDRX),   ///< End of RXD buffer reached.
    HAL_SPIM_EVENT_END     = offsetof(NRF_SPIM_Type, EVENTS_END),     ///< End of RXD buffer and TXD buffer reached.
    HAL_SPIM_EVENT_ENDTX   = offsetof(NRF_SPIM_Type, EVENTS_ENDTX),   ///< End of TXD buffer reached.
    HAL_SPIM_EVENT_STARTED = offsetof(NRF_SPIM_Type, EVENTS_STARTED)  ///< Transaction started.
} hal_spim_event_t;


typedef enum
{
    HAL_SPIM_SHORT_END_START_MASK = SPIM_SHORTS_END_START_Msk,
    HAL_SPIM_SHORT_ALL_MASK = SPIM_SHORTS_END_START_Msk,
} hal_spim_short_mask_t;

/** @brief SPIM interrupts. */
typedef enum
{
    HAL_SPIM_INT_STOPPED_MASK = SPIM_INTENSET_STOPPED_Msk,  ///< Interrupt on STOPPED event.
    HAL_SPIM_INT_ENDRX_MASK   = SPIM_INTENSET_ENDRX_Msk,    ///< Interrupt on ENDRX event.
    HAL_SPIM_INT_END_MASK     = SPIM_INTENSET_END_Msk,      ///< Interrupt on END event.
    HAL_SPIM_INT_ENDTX_MASK   = SPIM_INTENSET_ENDTX_Msk,    ///< Interrupt on ENDTX event.
    HAL_SPIM_INT_STARTED_MASK = SPIM_INTENSET_STARTED_Msk,  ///< Interrupt on STARTED event.
    HAL_SPIM_ALL_INTS_MASK    = SPIM_INTENSET_STOPPED_Msk |
                                SPIM_INTENSET_ENDRX_Msk   |
                                SPIM_INTENSET_END_Msk     |
                                SPIM_INTENSET_ENDTX_Msk   |
                                SPIM_INTENSET_STARTED_Msk   ///< All SPIM interrupts.
} hal_spim_int_mask_t;

/** @brief SPI master data rates. */
typedef enum
{
    HAL_SPIM_FREQ_125K = SPIM_FREQUENCY_FREQUENCY_K125,    ///< 125 kbps.
    HAL_SPIM_FREQ_250K = SPIM_FREQUENCY_FREQUENCY_K250,    ///< 250 kbps.
    HAL_SPIM_FREQ_500K = SPIM_FREQUENCY_FREQUENCY_K500,    ///< 500 kbps.
    HAL_SPIM_FREQ_1M   = SPIM_FREQUENCY_FREQUENCY_M1,      ///< 1 Mbps.
    HAL_SPIM_FREQ_2M   = SPIM_FREQUENCY_FREQUENCY_M2,      ///< 2 Mbps.
    HAL_SPIM_FREQ_4M   = SPIM_FREQUENCY_FREQUENCY_M4,      ///< 4 Mbps.
    // [conversion to 'int' needed to prevent compilers from complaining
    //  that the provided value (0x80000000UL) is out of range of "int"]
    HAL_SPIM_FREQ_8M   = (int)SPIM_FREQUENCY_FREQUENCY_M8, ///< 8 Mbps.
    HAL_SPIM_FREQ_16M  = SPIM_FREQUENCY_FREQUENCY_M16,     ///< 16 Mbps.
    HAL_SPIM_FREQ_32M  = SPIM_FREQUENCY_FREQUENCY_M32      ///< 32 Mbps.
} hal_spim_frequency_t;

/** @brief SPI modes. */
typedef enum
{
    HAL_SPIM_MODE_0, ///< SCK active high, sample on leading edge of clock.
    HAL_SPIM_MODE_1, ///< SCK active high, sample on trailing edge of cloHAL
    HAL_SPIM_MODE_2, ///< SCK active low, sample on leading edge of clock.
    HAL_SPIM_MODE_3  ///< SCK active low, sample on trailing edge of clock.
} hal_spim_mode_t;




#ifdef __cplusplus
}
#endif
#endif
