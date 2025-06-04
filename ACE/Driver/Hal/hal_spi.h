/******************************************************************************/
/*! @addtogroup Group2
    @file       hal_spi.h
    @brief      
    @date       2025/05/29
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _HAL_SPI_H_
#define _HAL_SPI_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include "hal_common.h"

/**
 * @brief This value can be used as a parameter for the @ref nrf_spi_pins_set
 *        function to specify that a given SPI signal (SCK, MOSI, or MISO)
 *        shall not be connected to a physical pin.
 */
#define HAL_SPI_PIN_NOT_CONNECTED  0xFFFFFFFF

/** @brief SPI events. */
typedef enum
{
    HAL_SPI_EVENT_READY = offsetof(NRF_SPI_Type, EVENTS_READY) ///< TXD byte sent and RXD byte received.
} hal_spi_event_t;


#ifdef __cplusplus
}
#endif
#endif
