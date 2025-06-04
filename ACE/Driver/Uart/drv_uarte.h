/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_uarte.h
    @brief      
    @date       2025/05/23
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#ifndef _DRV_UARTE_H_
#define _DRV_UARTE_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include "drv_common.h"

/** @brief Pin disconnected value. */
#define HAL_UARTE_PSEL_DISCONNECTED 0xFFFFFFFF

#define drv_uarte_parity_t hal_uarte_parity_t
#define drv_uarte_hwfc_t hal_uarte_hwfc_t
#define drv_uarte_stopbit_t hal_uarte_stopbit_t
#define drv_uarte_baudrate_t hal_uarte_baudrate_t


typedef enum
{
    DRV_UARTE_EVENT_TX_DONE,
    DRV_UARTE_EVENT_RX_DONE,
    DRV_UARTE_EVENT_ERROR
} drv_uarte_event;

typedef struct 
{
    uint8_t *data;
    uint32_t bytes;
}drv_uarte_xfer_evt_t;

typedef struct 
{
    drv_uarte_xfer_evt_t rxtx;
    uint32_t error_mask;
}drv_uarte_error_evt_t;

typedef struct 
{
    drv_uarte_event evt;
    union 
    {
        /* data */
        drv_uarte_xfer_evt_t rxtx;
        drv_uarte_error_evt_t error;
    }data;
    
}drv_uarte_evt_t;

typedef void (*drv_uarte_handler_t)(drv_uarte_event evt, void *p_context);

typedef struct 
{
    uint32_t tdx_pin;
    uint32_t rdx_pin;
    uint32_t cts_pin;
    uint32_t rts_pin;
    drv_uarte_parity_t parity;
    drv_uarte_hwfc_t hwfc;
    drv_uarte_stopbit_t stopbit;
    drv_uarte_baudrate_t baudrate;
    void *p_context;
    drv_uarte_handler_t func;
}drv_uarte_config_t;

typedef struct DRV_UART_S drv_uarte_t;
struct DRV_UART_S
{
    /* data */
    NRF_UARTE_Type *reg;
    uint8_t drv_index;
    drv_uarte_config_t cfg;
    drv_sta_t (*drv_uarte_config)(drv_uarte_t *self, drv_uarte_handler_t drv_uarte_handler);
    drv_sta_t (*drv_uarte_send_data)(drv_uarte_t *self, uint8_t *data, uint32_t len);
    drv_sta_t (*drv_uarte_send_data_it)(drv_uarte_t *self, uint8_t *data, uint32_t len);
    drv_sta_t (*drv_uarte_received)(drv_uarte_t *self, uint8_t *data);
};

#define DRV_UARTE_INSTANCE0                                                     \
{                                                                               \
    .reg                = NRF_UARTE0,                                           \
    .drv_index          = 0,                                                    \
    .cfg                = DRV_UARTE_DEFAULT_CONFIG,                             \
    .drv_uarte_config = NULL,                                                   \
    .drv_uarte_send_data_it = NULL,                                             \
    .drv_uarte_send_data = NULL,                                                \
    .drv_uarte_received = NULL,                                                 \
}

#define DRV_UARTE_INSTANCE1                                                     \
{                                                                               \
    .reg                = NRF_UARTE1,                                           \
    .drv_index          = 1,                                                    \
    .cfg                = DRV_UARTE_DEFAULT_CONFIG,                             \
    .drv_uarte_config = NULL,                                                   \
    .drv_uarte_send_data_it = NULL,                                             \
    .drv_uarte_send_data = NULL,                                                \
    .drv_uarte_received = NULL,                                                 \
}

#define DRV_UARTE_DEFAULT_CONFIG                                                     \
{                                                                                   \
    .tdx_pin            = HAL_UARTE_PSEL_DISCONNECTED,                               \
    .rdx_pin            = HAL_UARTE_PSEL_DISCONNECTED,                               \
    .cts_pin            = HAL_UARTE_PSEL_DISCONNECTED,                               \
    .rts_pin            = HAL_UARTE_PSEL_DISCONNECTED,                               \
    .parity             = (drv_uarte_parity_t)HAL_UARTE_PARITY_EXCLUDED,              \
    .hwfc               = (drv_uarte_hwfc_t)HAL_UARTE_HWFC_DISABLED,                  \
    .stopbit            = (drv_uarte_stopbit_t)HAL_UARTE_STOPBIT_ONE,                 \
    .baudrate           = (drv_uarte_baudrate_t)HAL_UARTE_BAUDRATE_115200,            \
    .p_context          = (void*)NULL,                                              \
    .func               = (drv_uarte_handler_t)NULL,                                \
}


/* UART PORT/PIN */
#define DRV_UARTE_PSEL_CONNECT_POS   31UL /**< Pin connected. */
#define DRV_UARTE_PSEL_CONNECT      (0UL << DRV_UARTE_PSEL_CONNECT_POS) /**< Pin connected. */
#define DRV_UARTE_PSEL_DISCONNECT   (1UL << DRV_UARTE_PSEL_CONNECT_POS) /**< Pin disconnected. */

#define DRV_UARTE_PSEL_PORT_POS  0x05UL /**< Port number. */
#define DRV_UARTE_PSEL_PIN_POS   0x00UL /**< Pin number. */
#define DRV_UARTE_PSEL_SETUP(port, pin) \
    ( (DRV_UARTE_PSEL_CONNECT)\
    | ((pin) << DRV_UARTE_PSEL_PIN_POS)\
    | ((port) << DRV_UARTE_PSEL_PORT_POS))\

extern drv_uarte_t *drv_uarte_create(uint8_t index);


#ifdef __cplusplus
}
#endif
#endif