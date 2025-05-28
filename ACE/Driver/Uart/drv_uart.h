/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_uart.h
    @brief      
    @date       2025/05/23
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#ifndef _DRV_UART_H_
#define _DRV_UART_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* Code here */
#include "drv_common.h"

#define drv_uart_parity_t hal_uart_parity_t
#define drv_uart_hwfc_t hal_uart_hwfc_t
#define drv_uart_stopbit_t hal_uart_stopbit_t
#define drv_uart_baudrate_t hal_uart_baudrate_t

typedef enum
{
    DRV_UART_EVENT_TX_DONE,
    DRV_UART_EVENT_RX_DONE,
    DRV_UART_EVENT_ERROR
} drv_uart_event;

typedef struct 
{
    uint8_t *data;
    uint32_t bytes;
}drv_uart_xfer_evt_t;

typedef struct 
{
    drv_uart_xfer_evt_t rxtx;
    uint32_t error_mask;
}drv_uart_error_evt_t;

typedef struct 
{
    drv_uart_event evet;
    union 
    {
        /* data */
        drv_uart_xfer_evt_t rxtx;
        drv_uart_error_evt_t error;
    }data;
    
}drv_uart_evt_t;


typedef void (*drv_uart_handler_t)(drv_uart_event evt, void *p_context);

typedef struct
{
    uint32_t tdx_pin;
    uint32_t rdx_pin;
    uint32_t cts_pin;
    uint32_t rts_pin;
    drv_uart_parity_t parity;
    drv_uart_hwfc_t hwfc;
    drv_uart_stopbit_t stopbit;
    drv_uart_baudrate_t baudrate;
    void *p_context;
    drv_uart_handler_t func;
} drv_uart_config_t;

typedef struct
{
    NRF_UART_Type *reg;
    uint8_t drv_initialized;
    drv_uart_config_t cfg;
}drv_uart_t;

#define DRV_UART_INSTANCE0                                                      \
{                                                                               \
    .reg                = NRF_UART0,                                            \
    .drv_initialized    = 0,                                                    \
    .cfg                = (drv_uart_config_t)DRV_UART_DEFAULT_CONFIG,           \
}

#define DRV_UART_DEFAULT_CONFIG                                                     \
{                                                                                   \
    .tdx_pin            = HAL_UART_PSEL_DISCONNECTED,                               \
    .rdx_pin            = HAL_UART_PSEL_DISCONNECTED,                               \
    .cts_pin            = HAL_UART_PSEL_DISCONNECTED,                               \
    .rts_pin            = HAL_UART_PSEL_DISCONNECTED,                               \
    .parity             = (drv_uart_parity_t)HAL_UART_PARITY_EXCLUDED,              \
    .hwfc               = (drv_uart_hwfc_t)HAL_UART_HWFC_DISABLED,                  \
    .stopbit            = (drv_uart_stopbit_t)HAL_UART_STOPBIT_ONE,                 \
    .baudrate           = (drv_uart_baudrate_t)HAL_UART_BAUDRATE_115200,            \
    .p_context          = (void*)NULL,                                              \
    .func               = (drv_uart_handler_t)NULL,                                \
}

/* UART PORT/PIN */
#define DRV_UART_PSEL_CONNECT_POS   31UL /**< Pin connected. */
#define DRV_UART_PSEL_CONNECT      (0UL << DRV_UART_PSEL_CONNECT_POS) /**< Pin connected. */
#define DRV_UART_PSEL_DISCONNECT   (1UL << DRV_UART_PSEL_CONNECT_POS) /**< Pin disconnected. */

#define DRV_UART_PSEL_PORT_POS  0x05UL /**< Port number. */
#define DRV_UART_PSEL_PIN_POS   0x00UL /**< Pin number. */
#define DRV_UART_PSEL_SETUP(port, pin) \
    ( (DRV_UART_PSEL_CONNECT)\
    | ((pin) << DRV_UART_PSEL_PIN_POS)\
    | ((port) << DRV_UART_PSEL_PORT_POS))\

#define DRV_UART_BUFFER_MAX 256
#define DRV_UART_BUFEER_MASK (DRV_UART_BUFFER_MAX - 1)
typedef struct 
{
    uint8_t data[DRV_UART_BUFFER_MAX];
    uint32_t head;
    uint32_t tail;
}drv_uart_ring_buffer_t;



extern drv_sta_t drv_uart_init(uint8_t index);
extern drv_sta_t drv_uart_deinit();
extern drv_sta_t drv_uart_config(drv_uart_handler_t func);
extern drv_sta_t drv_uart_send_data(uint8_t *data, uint16_t len);
extern drv_sta_t drv_uart_received_polling(uint8_t *data, uint32_t len);
extern drv_sta_t drv_uart_send_data_it(uint8_t *data, uint16_t len);

#ifdef __cplusplus
}
#endif
#endif
