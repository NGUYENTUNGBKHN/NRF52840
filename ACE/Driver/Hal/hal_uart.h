/******************************************************************************/
/*! @addtogroup Group2
    @file       hal_uart.h
    @brief      
    @date       2025/05/21
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _HAL_UART_H_
#define _HAL_UART_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include "hal_common.h"

/** @brief Pin disconnected value. */
#define HAL_UART_PSEL_DISCONNECTED 0xFFFFFFFF

typedef enum
{
    HAL_UART_TASK_STARTRX = offsetof(NRF_UART_Type, TASKS_STARTRX), /**< Task for starting reception. */
    HAL_UART_TASK_STOPRX  = offsetof(NRF_UART_Type, TASKS_STOPRX),  /**< Task for stopping reception. */
    HAL_UART_TASK_STARTTX = offsetof(NRF_UART_Type, TASKS_STARTTX), /**< Task for starting transmission. */
    HAL_UART_TASK_STOPTX  = offsetof(NRF_UART_Type, TASKS_STOPTX),  /**< Task for stopping transmission. */
    HAL_UART_TASK_SUSPEND = offsetof(NRF_UART_Type, TASKS_SUSPEND), /**< Task for suspending UART. */
}hal_uart_task_t;

typedef enum
{
    HAL_UART_EVENT_CTS    = offsetof(NRF_UART_Type, EVENTS_CTS),   /**< Event from CTS line activation. */
    HAL_UART_EVENT_NCTS   = offsetof(NRF_UART_Type, EVENTS_NCTS),  /**< Event from CTS line deactivation. */
    HAL_UART_EVENT_RXDRDY = offsetof(NRF_UART_Type, EVENTS_RXDRDY),/**< Event from data ready in RXD. */
    HAL_UART_EVENT_TXDRDY = offsetof(NRF_UART_Type, EVENTS_TXDRDY),/**< Event from data sent from TXD. */
    HAL_UART_EVENT_ERROR  = offsetof(NRF_UART_Type, EVENTS_ERROR), /**< Event from error detection. */
    HAL_UART_EVENT_RXTO   = offsetof(NRF_UART_Type, EVENTS_RXTO)   /**< Event from receiver timeout. */
}hal_uart_event_t;

typedef enum
{
    HAL_UART_INT_MASK_CTS    = UART_INTENCLR_CTS_Msk,    /**< CTS line activation interrupt. */
    HAL_UART_INT_MASK_NCTS   = UART_INTENCLR_NCTS_Msk,   /**< CTS line deactivation interrupt. */
    HAL_UART_INT_MASK_RXDRDY = UART_INTENCLR_RXDRDY_Msk, /**< Data ready in RXD interrupt. */
    HAL_UART_INT_MASK_TXDRDY = UART_INTENCLR_TXDRDY_Msk, /**< Data sent from TXD interrupt. */
    HAL_UART_INT_MASK_ERROR  = UART_INTENCLR_ERROR_Msk,  /**< Error detection interrupt. */
    HAL_UART_INT_MASK_RXTO   = UART_INTENCLR_RXTO_Msk    /**< Receiver timeout interrupt. */
}hal_uart_interrupt_mask_t;


typedef enum
{
    HAL_UART_BAUDRATE_1200    = UART_BAUDRATE_BAUDRATE_Baud1200,   /**< 1200 baud. */
    HAL_UART_BAUDRATE_2400    = UART_BAUDRATE_BAUDRATE_Baud2400,   /**< 2400 baud. */
    HAL_UART_BAUDRATE_4800    = UART_BAUDRATE_BAUDRATE_Baud4800,   /**< 4800 baud. */
    HAL_UART_BAUDRATE_9600    = UART_BAUDRATE_BAUDRATE_Baud9600,   /**< 9600 baud. */
    HAL_UART_BAUDRATE_14400   = UART_BAUDRATE_BAUDRATE_Baud14400,  /**< 14400 baud. */
    HAL_UART_BAUDRATE_19200   = UART_BAUDRATE_BAUDRATE_Baud19200,  /**< 19200 baud. */
    HAL_UART_BAUDRATE_28800   = UART_BAUDRATE_BAUDRATE_Baud28800,  /**< 28800 baud. */
    HAL_UART_BAUDRATE_31250   = UART_BAUDRATE_BAUDRATE_Baud31250,  /**< 31250 baud. */
    HAL_UART_BAUDRATE_38400   = UART_BAUDRATE_BAUDRATE_Baud38400,  /**< 38400 baud. */
    HAL_UART_BAUDRATE_56000   = UART_BAUDRATE_BAUDRATE_Baud56000,  /**< 56000 baud. */
    HAL_UART_BAUDRATE_57600   = UART_BAUDRATE_BAUDRATE_Baud57600,  /**< 57600 baud. */
    HAL_UART_BAUDRATE_76800   = UART_BAUDRATE_BAUDRATE_Baud76800,  /**< 76800 baud. */
    HAL_UART_BAUDRATE_115200  = UART_BAUDRATE_BAUDRATE_Baud115200, /**< 115200 baud. */
    HAL_UART_BAUDRATE_230400  = UART_BAUDRATE_BAUDRATE_Baud230400, /**< 230400 baud. */
    HAL_UART_BAUDRATE_250000  = UART_BAUDRATE_BAUDRATE_Baud250000, /**< 250000 baud. */
    HAL_UART_BAUDRATE_460800  = UART_BAUDRATE_BAUDRATE_Baud460800, /**< 460800 baud. */
    HAL_UART_BAUDRATE_921600  = UART_BAUDRATE_BAUDRATE_Baud921600, /**< 921600 baud. */
    HAL_UART_BAUDRATE_1000000 = UART_BAUDRATE_BAUDRATE_Baud1M,     /**< 1000000 baud. */
}hal_uart_baudrate_t;

typedef enum
{
    HAL_UART_ERROR_OVERRUN_MASK = UART_ERRORSRC_OVERRUN_Msk,   /**< Overrun error. */
    HAL_UART_ERROR_PARITY_MASK  = UART_ERRORSRC_PARITY_Msk,    /**< Parity error. */
    HAL_UART_ERROR_FRAMING_MASK = UART_ERRORSRC_FRAMING_Msk,   /**< Framing error. */
    HAL_UART_ERROR_BREAK_MASK   = UART_ERRORSRC_BREAK_Msk,     /**< Break error. */
}hal_uart_error_mask_t;

typedef enum
{
    HAL_UART_PARITY_EXCLUDED = UART_CONFIG_PARITY_Excluded << UART_CONFIG_PARITY_Pos, /**< Parity excluded. */
    HAL_UART_PARITY_INCLUDED = UART_CONFIG_PARITY_Included << UART_CONFIG_PARITY_Pos, /**< Parity included. */
}hal_uart_parity_t;

typedef enum
{
    HAL_UART_HWFC_DISABLED = UART_CONFIG_HWFC_Disabled, /**< Hardware flow control disabled. */
    HAL_UART_HWFC_ENABLED  = UART_CONFIG_HWFC_Enabled,  /**< Hardware flow control enabled. */
}hal_uart_hwfc_t;

typedef enum
{
    HAL_UART_STOPBIT_ONE = UART_CONFIG_STOP_One << UART_CONFIG_STOP_Pos, /**< Stopbit control one mode. */
    HAL_UART_STOPBIT_TWO = UART_CONFIG_STOP_Two << UART_CONFIG_STOP_Pos,  /**< Stopbit control two mode. */
}hal_uart_stopbit_t;

/* Event */
__STATIC_INLINE void hal_uart_event_clear(NRF_UART_Type * p_reg, hal_uart_event_t event)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event)) = 0x0UL;
}

__STATIC_INLINE bool hal_uart_event_check(NRF_UART_Type * p_reg, hal_uart_event_t event)
{
    return (bool)*(volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event);
}

__STATIC_INLINE uint32_t hal_uart_event_address_get(NRF_UART_Type  * p_reg,
                                                    hal_uart_event_t event)
{
    return (uint32_t)((uint8_t *)p_reg + (uint32_t)event);
}
/* Interrupt */
__STATIC_INLINE void hal_uart_int_enable(NRF_UART_Type * p_reg, uint32_t mask)
{
    p_reg->INTENSET = mask;
}

__STATIC_INLINE bool hal_uart_int_enable_check(NRF_UART_Type * p_reg, uint32_t mask)
{
    return (bool)(p_reg->INTENSET & mask);
}

__STATIC_INLINE void hal_uart_int_disable(NRF_UART_Type * p_reg, uint32_t mask)
{
    p_reg->INTENCLR = mask;
}

__STATIC_INLINE uint32_t hal_uart_errorsrc_get_and_clear(NRF_UART_Type * p_reg)
{
    uint32_t errsrc_mask = p_reg->ERRORSRC;
    p_reg->ERRORSRC = errsrc_mask;
    return errsrc_mask;
}

__STATIC_INLINE void hal_uart_enable(NRF_UART_Type * p_reg)
{
    p_reg->ENABLE = UART_ENABLE_ENABLE_Enabled;
}

__STATIC_INLINE void hal_uart_disable(NRF_UART_Type * p_reg)
{
    p_reg->ENABLE = UART_ENABLE_ENABLE_Disabled;
}

__STATIC_INLINE void hal_uart_txrx_pins_set(NRF_UART_Type * p_reg, uint32_t pseltxd, uint32_t pselrxd)
{
    p_reg->PSEL.RXD = pselrxd;
    p_reg->PSEL.TXD = pseltxd;
}

__STATIC_INLINE void hal_uart_txrx_pins_disconnect(NRF_UART_Type * p_reg)
{
    hal_uart_txrx_pins_set(p_reg, HAL_UART_PSEL_DISCONNECTED, HAL_UART_PSEL_DISCONNECTED);
}

__STATIC_INLINE uint32_t hal_uart_tx_pin_get(NRF_UART_Type * p_reg)
{
    return p_reg->PSEL.TXD;
}

__STATIC_INLINE uint32_t hal_uart_rx_pin_get(NRF_UART_Type * p_reg)
{
    return p_reg->PSEL.RXD;
}

__STATIC_INLINE uint32_t hal_uart_rts_pin_get(NRF_UART_Type * p_reg)
{
    return p_reg->PSEL.RTS;
}

__STATIC_INLINE uint32_t hal_uart_cts_pin_get(NRF_UART_Type * p_reg)
{
    return p_reg->PSEL.CTS;
}

__STATIC_INLINE void hal_uart_hwfc_pins_set(NRF_UART_Type * p_reg, uint32_t pselrts, uint32_t pselcts)
{
    p_reg->PSEL.RTS = pselrts;
    p_reg->PSEL.CTS = pselcts;
}

__STATIC_INLINE void hal_uart_hwfc_pins_disconnect(NRF_UART_Type * p_reg)
{
    hal_uart_hwfc_pins_set(p_reg, HAL_UART_PSEL_DISCONNECTED, HAL_UART_PSEL_DISCONNECTED);
}

__STATIC_INLINE uint8_t hal_uart_rxd_get(NRF_UART_Type * p_reg)
{
    return p_reg->RXD;
}

__STATIC_INLINE void hal_uart_txd_set(NRF_UART_Type * p_reg, uint8_t txd)
{
    p_reg->TXD = txd;
}

__STATIC_INLINE void hal_uart_task_trigger(NRF_UART_Type * p_reg, hal_uart_task_t task)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)task)) = 0x1UL;
}

__STATIC_INLINE uint32_t hal_uart_task_address_get(NRF_UART_Type * p_reg, hal_uart_task_t task)
{
    return (uint32_t)p_reg + (uint32_t)task;
}

__STATIC_INLINE void hal_uart_configure(NRF_UART_Type   * p_reg,
                                            hal_uart_parity_t parity,
                                            hal_uart_hwfc_t   hwfc,
                                            hal_uart_stopbit_t stopbit)
{
    p_reg->CONFIG = ((uint32_t)parity |
                     (uint32_t)hwfc | 
                     (uint32_t)stopbit);
}

__STATIC_INLINE void hal_uart_baudrate_set(NRF_UART_Type * p_reg, hal_uart_baudrate_t baudrate)
{
    p_reg->BAUDRATE = baudrate;
}

#ifdef __cplusplus
}
#endif
#endif



