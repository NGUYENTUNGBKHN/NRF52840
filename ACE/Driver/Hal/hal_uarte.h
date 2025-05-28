/******************************************************************************/
/*! @addtogroup Group2
    @file       hal_uarte.h
    @brief      
    @date       2025/05/23
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#ifndef _HAL_UARTE_H_
#define _HAL_UARTE_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include "hal_common.h"

#define HAL_UARTE_PSEL_DISCONNECTED 0xFFFFFFFF

/**
 * @defgroup hal_uarte_hal UARTE HAL
 * @{
 * @ingroup hal_uarte
 * @brief   Hardware access layer for managing the UARTE peripheral.
 */

/** @brief UARTE tasks. */
typedef enum
{
    HAL_UARTE_TASK_STARTRX   = offsetof(NRF_UARTE_Type, TASKS_STARTRX), ///< Start UART receiver.
    HAL_UARTE_TASK_STOPRX    = offsetof(NRF_UARTE_Type, TASKS_STOPRX),  ///< Stop UART receiver.
    HAL_UARTE_TASK_STARTTX   = offsetof(NRF_UARTE_Type, TASKS_STARTTX), ///< Start UART transmitter.
    HAL_UARTE_TASK_STOPTX    = offsetof(NRF_UARTE_Type, TASKS_STOPTX),  ///< Stop UART transmitter.
    HAL_UARTE_TASK_FLUSHRX   = offsetof(NRF_UARTE_Type, TASKS_FLUSHRX)  ///< Flush RX FIFO in RX buffer.
} hal_uarte_task_t;

/** @brief UARTE events. */
typedef enum
{
    HAL_UARTE_EVENT_CTS       = offsetof(NRF_UARTE_Type, EVENTS_CTS),       ///< CTS is activated.
    HAL_UARTE_EVENT_NCTS      = offsetof(NRF_UARTE_Type, EVENTS_NCTS),      ///< CTS is deactivated.
    HAL_UARTE_EVENT_RXDRDY    = offsetof(NRF_UARTE_Type, EVENTS_RXDRDY),    ///< Data received in RXD (but potentially not yet transferred to Data RAM).
    HAL_UARTE_EVENT_ENDRX     = offsetof(NRF_UARTE_Type, EVENTS_ENDRX),     ///< Receive buffer is filled up.
    HAL_UARTE_EVENT_TXDRDY    = offsetof(NRF_UARTE_Type, EVENTS_TXDRDY),    ///< Data sent from TXD.
    HAL_UARTE_EVENT_ENDTX     = offsetof(NRF_UARTE_Type, EVENTS_ENDTX),     ///< Last TX byte transmitted.
    HAL_UARTE_EVENT_ERROR     = offsetof(NRF_UARTE_Type, EVENTS_ERROR),     ///< Error detected.
    HAL_UARTE_EVENT_RXTO      = offsetof(NRF_UARTE_Type, EVENTS_RXTO),      ///< Receiver timeout.
    HAL_UARTE_EVENT_RXSTARTED = offsetof(NRF_UARTE_Type, EVENTS_RXSTARTED), ///< Receiver has started.
    HAL_UARTE_EVENT_TXSTARTED = offsetof(NRF_UARTE_Type, EVENTS_TXSTARTED), ///< Transmitter has started.
    HAL_UARTE_EVENT_TXSTOPPED = offsetof(NRF_UARTE_Type, EVENTS_TXSTOPPED)  ///< Transmitted stopped.
} hal_uarte_event_t;

/** @brief Types of UARTE shortcuts. */
typedef enum
{
    HAL_UARTE_SHORT_ENDRX_STARTRX = UARTE_SHORTS_ENDRX_STARTRX_Msk, ///< Shortcut between ENDRX event and STARTRX task.
    HAL_UARTE_SHORT_ENDRX_STOPRX  = UARTE_SHORTS_ENDRX_STOPRX_Msk   ///< Shortcut between ENDRX event and STOPRX task.
} hal_uarte_short_t;


/** @brief UARTE interrupts. */
typedef enum
{
    HAL_UARTE_INT_CTS_MASK       = UARTE_INTENSET_CTS_Msk,       ///< Interrupt on CTS event.
    HAL_UARTE_INT_NCTS_MASK      = UARTE_INTENSET_NCTS_Msk,      ///< Interrupt on NCTS event.
    HAL_UARTE_INT_RXDRDY_MASK    = UARTE_INTENSET_RXDRDY_Msk,    ///< Interrupt on RXDRDY event.
    HAL_UARTE_INT_ENDRX_MASK     = UARTE_INTENSET_ENDRX_Msk,     ///< Interrupt on ENDRX event.
    HAL_UARTE_INT_TXDRDY_MASK    = UARTE_INTENSET_TXDRDY_Msk,    ///< Interrupt on TXDRDY event.
    HAL_UARTE_INT_ENDTX_MASK     = UARTE_INTENSET_ENDTX_Msk,     ///< Interrupt on ENDTX event.
    HAL_UARTE_INT_ERROR_MASK     = UARTE_INTENSET_ERROR_Msk,     ///< Interrupt on ERROR event.
    HAL_UARTE_INT_RXTO_MASK      = UARTE_INTENSET_RXTO_Msk,      ///< Interrupt on RXTO event.
    HAL_UARTE_INT_RXSTARTED_MASK = UARTE_INTENSET_RXSTARTED_Msk, ///< Interrupt on RXSTARTED event.
    HAL_UARTE_INT_TXSTARTED_MASK = UARTE_INTENSET_TXSTARTED_Msk, ///< Interrupt on TXSTARTED event.
    HAL_UARTE_INT_TXSTOPPED_MASK = UARTE_INTENSET_TXSTOPPED_Msk  ///< Interrupt on TXSTOPPED event.
} hal_uarte_int_mask_t;

/** @brief Baudrates supported by UARTE. */
typedef enum
{
    HAL_UARTE_BAUDRATE_1200    = UARTE_BAUDRATE_BAUDRATE_Baud1200,   ///< 1200 baud.
    HAL_UARTE_BAUDRATE_2400    = UARTE_BAUDRATE_BAUDRATE_Baud2400,   ///< 2400 baud.
    HAL_UARTE_BAUDRATE_4800    = UARTE_BAUDRATE_BAUDRATE_Baud4800,   ///< 4800 baud.
    HAL_UARTE_BAUDRATE_9600    = UARTE_BAUDRATE_BAUDRATE_Baud9600,   ///< 9600 baud.
    HAL_UARTE_BAUDRATE_14400   = UARTE_BAUDRATE_BAUDRATE_Baud14400,  ///< 14400 baud.
    HAL_UARTE_BAUDRATE_19200   = UARTE_BAUDRATE_BAUDRATE_Baud19200,  ///< 19200 baud.
    HAL_UARTE_BAUDRATE_28800   = UARTE_BAUDRATE_BAUDRATE_Baud28800,  ///< 28800 baud.
    HAL_UARTE_BAUDRATE_31250   = UARTE_BAUDRATE_BAUDRATE_Baud31250,  ///< 31250 baud.
    HAL_UARTE_BAUDRATE_38400   = UARTE_BAUDRATE_BAUDRATE_Baud38400,  ///< 38400 baud.
    HAL_UARTE_BAUDRATE_56000   = UARTE_BAUDRATE_BAUDRATE_Baud56000,  ///< 56000 baud.
    HAL_UARTE_BAUDRATE_57600   = UARTE_BAUDRATE_BAUDRATE_Baud57600,  ///< 57600 baud.
    HAL_UARTE_BAUDRATE_76800   = UARTE_BAUDRATE_BAUDRATE_Baud76800,  ///< 76800 baud.
    HAL_UARTE_BAUDRATE_115200  = UARTE_BAUDRATE_BAUDRATE_Baud115200, ///< 115200 baud.
    HAL_UARTE_BAUDRATE_230400  = UARTE_BAUDRATE_BAUDRATE_Baud230400, ///< 230400 baud.
    HAL_UARTE_BAUDRATE_250000  = UARTE_BAUDRATE_BAUDRATE_Baud250000, ///< 250000 baud.
    HAL_UARTE_BAUDRATE_460800  = UARTE_BAUDRATE_BAUDRATE_Baud460800, ///< 460800 baud.
    HAL_UARTE_BAUDRATE_921600  = UARTE_BAUDRATE_BAUDRATE_Baud921600, ///< 921600 baud.
    HAL_UARTE_BAUDRATE_1000000 = UARTE_BAUDRATE_BAUDRATE_Baud1M      ///< 1000000 baud.
} hal_uarte_baudrate_t;

/** @brief Types of UARTE error masks. */
typedef enum
{
    HAL_UARTE_ERROR_OVERRUN_MASK = UARTE_ERRORSRC_OVERRUN_Msk, ///< Overrun error.
    HAL_UARTE_ERROR_PARITY_MASK  = UARTE_ERRORSRC_PARITY_Msk,  ///< Parity error.
    HAL_UARTE_ERROR_FRAMING_MASK = UARTE_ERRORSRC_FRAMING_Msk, ///< Framing error.
    HAL_UARTE_ERROR_BREAK_MASK   = UARTE_ERRORSRC_BREAK_Msk    ///< Break error.
} hal_uarte_error_mask_t;

/** @brief Types of UARTE parity modes. */
typedef enum
{
    HAL_UARTE_PARITY_EXCLUDED = UARTE_CONFIG_PARITY_Excluded << UARTE_CONFIG_PARITY_Pos, ///< Parity excluded.
    HAL_UARTE_PARITY_INCLUDED = UARTE_CONFIG_PARITY_Included << UARTE_CONFIG_PARITY_Pos  ///< Parity included.
} hal_uarte_parity_t;

/** @brief Types of UARTE flow control modes. */
typedef enum
{
    HAL_UARTE_HWFC_DISABLED = UARTE_CONFIG_HWFC_Disabled << UARTE_CONFIG_HWFC_Pos, ///< Hardware flow control disabled.
    HAL_UARTE_HWFC_ENABLED  = UARTE_CONFIG_HWFC_Enabled  << UARTE_CONFIG_HWFC_Pos  ///< Hardware flow control enabled.
} hal_uarte_hwfc_t;

/**
 * @brief Types of UARTE stop bit modes.
 */
typedef enum
{
    HAL_UARTE_STOPBIT_ONE = UARTE_CONFIG_STOP_One << UARTE_CONFIG_STOP_Pos,
    HAL_UARTE_STOPBIT_TWO = UARTE_CONFIG_STOP_Two << UARTE_CONFIG_STOP_Pos
} hal_uarte_stopbit_t;

/* Event */
__STATIC_INLINE void hal_uarte_event_clear(NRF_UARTE_Type * p_reg, hal_uarte_event_t event)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event)) = 0x0UL;
}

__STATIC_INLINE bool hal_uarte_event_check(NRF_UARTE_Type * p_reg, hal_uarte_event_t event)
{
    return (bool)*(volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event);
}

__STATIC_INLINE uint32_t hal_uarte_event_address_get(NRF_UARTE_Type  * p_reg,
                                                    hal_uarte_event_t  event)
{
    return (uint32_t)((uint8_t *)p_reg + (uint32_t)event);
}

/* SHORT */
__STATIC_INLINE void hal_uarte_shorts_enable(NRF_UARTE_Type * p_reg, hal_uarte_short_t mask)
{
    p_reg->SHORTS |= mask;
}

__STATIC_INLINE void hal_uarte_shorts_disable(NRF_UARTE_Type * p_reg, hal_uarte_short_t mask)
{
    p_reg->SHORTS &= ~(mask);
}

/* Interrupt */
__STATIC_INLINE void hal_uarte_int_enable(NRF_UARTE_Type * p_reg, hal_uarte_int_mask_t mask)
{
    p_reg->INTENSET = mask;
}

__STATIC_INLINE bool hal_uarte_int_enable_check(NRF_UARTE_Type * p_reg, hal_uarte_int_mask_t mask)
{
    return (bool)(p_reg->INTENSET & mask);
}

__STATIC_INLINE void hal_uarte_int_disable(NRF_UARTE_Type * p_reg, hal_uarte_int_mask_t mask)
{
    p_reg->INTENCLR = mask;
}
/* Task */
__STATIC_INLINE void hal_uarte_task_trigger(NRF_UARTE_Type * p_reg, hal_uarte_task_t task)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)task)) = 0x1UL;
}

__STATIC_INLINE uint32_t hal_uarte_task_address_get(NRF_UARTE_Type * p_reg, hal_uarte_task_t task)
{
    return (uint32_t)p_reg + (uint32_t)task;
}

__STATIC_INLINE uint32_t hal_uarte_errorsrc_get_and_clear(NRF_UARTE_Type * p_reg)
{
    uint32_t errsrc_mask = p_reg->ERRORSRC;
    p_reg->ERRORSRC = errsrc_mask;
    return errsrc_mask;
}

__STATIC_INLINE void hal_uarte_enable(NRF_UARTE_Type * p_reg)
{
    p_reg->ENABLE = UARTE_ENABLE_ENABLE_Enabled;
}

__STATIC_INLINE void hal_uarte_disable(NRF_UARTE_Type * p_reg)
{
    p_reg->ENABLE = UARTE_ENABLE_ENABLE_Disabled;
}

__STATIC_INLINE void hal_uarte_txrx_pins_set(NRF_UARTE_Type * p_reg, uint32_t pseltxd, uint32_t pselrxd)
{
    p_reg->PSEL.TXD = pseltxd;
    p_reg->PSEL.RXD = pselrxd;
}

__STATIC_INLINE void hal_uarte_txrx_pins_disconnect(NRF_UARTE_Type * p_reg)
{
    hal_uarte_txrx_pins_set(p_reg, HAL_UARTE_PSEL_DISCONNECTED, HAL_UARTE_PSEL_DISCONNECTED);
}

__STATIC_INLINE uint32_t hal_uarte_tx_pin_get(NRF_UARTE_Type * p_reg)
{
    return p_reg->PSEL.TXD;
}

__STATIC_INLINE uint32_t hal_uarte_rx_pin_get(NRF_UARTE_Type * p_reg)
{
    return p_reg->PSEL.RXD;
}

__STATIC_INLINE uint32_t hal_uarte_rts_pin_get(NRF_UARTE_Type * p_reg)
{
    return p_reg->PSEL.RTS;
}

__STATIC_INLINE uint32_t hal_uarte_cts_pin_get(NRF_UARTE_Type * p_reg)
{
    return p_reg->PSEL.CTS;
}

__STATIC_INLINE void hal_uarte_hwfc_pins_set(NRF_UARTE_Type * p_reg, uint32_t pselrts, uint32_t pselcts)
{
    p_reg->PSEL.RTS = pselrts;
    p_reg->PSEL.CTS = pselcts;
}

__STATIC_INLINE void hal_uarte_hwfc_pins_disconnect(NRF_UARTE_Type * p_reg)
{
    hal_uarte_hwfc_pins_set(p_reg, HAL_UARTE_PSEL_DISCONNECTED, HAL_UARTE_PSEL_DISCONNECTED);
}

__STATIC_INLINE void hal_uarte_configure(NRF_UARTE_Type   * p_reg,
                                         hal_uarte_parity_t parity,
                                         hal_uarte_hwfc_t   hwfc,
                                         hal_uarte_stopbit_t  stopbit)
{
    p_reg->CONFIG = (uint32_t)parity | (uint32_t)hwfc | (uint32_t)stopbit;
}

__STATIC_INLINE void hal_uarte_baudrate_set(NRF_UARTE_Type   * p_reg, hal_uarte_baudrate_t baudrate)
{
    p_reg->BAUDRATE = baudrate;
}

__STATIC_INLINE void hal_uarte_tx_buffer_set(NRF_UARTE_Type * p_reg,
                                             uint8_t  const * p_buffer,
                                             size_t           length)
{
    p_reg->TXD.PTR    = (uint32_t)p_buffer;
    p_reg->TXD.MAXCNT = length;
}

__STATIC_INLINE uint32_t hal_uarte_tx_amount_get(NRF_UARTE_Type * p_reg)
{
    return p_reg->TXD.AMOUNT;
}

__STATIC_INLINE void hal_uarte_rx_buffer_set(NRF_UARTE_Type * p_reg,
                                             uint8_t *        p_buffer,
                                             size_t           length)
{
    p_reg->RXD.PTR    = (uint32_t)p_buffer;
    p_reg->RXD.MAXCNT = length;
}

__STATIC_INLINE uint32_t hal_uarte_rx_amount_get(NRF_UARTE_Type * p_reg)
{
    return p_reg->RXD.AMOUNT;
}

#ifdef __cplusplus
}
#endif
#endif
