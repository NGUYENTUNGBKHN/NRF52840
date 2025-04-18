/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_uart.h
    @brief      
    @date       2025/04/16
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

/* CODE */
#include "nrf52840.h"
#include "nrf52840_bitfields.h"
#include "drv_common.h"


#define DRV_UART_PSEL_DISCONNECTED      0xFFFFFFFFUL /**< Pin disconnected. */


/*_______________________________________________________________________________________*/
/* UART ENABLE */

/** @brief Enable/Disable Register Uart */
typedef enum
{
    DRV_UART_ENABLE_REGISTER_EN = UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos,   /**< Enable uart. */
    DRV_UART_ENABLE_REGISTER_DIS = UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos,  /**< Disable uart. */
}drv_uart_en_reg_t;


/*_______________________________________________________________________________________*/
/* UART CONFIG */

/** @brief Baudrates supported by UART. */
typedef enum
{
    DRV_UART_CFG_BAUDRATE_1200    = UART_BAUDRATE_BAUDRATE_Baud1200,   /**< 1200 baud. */
    DRV_UART_CFG_BAUDRATE_2400    = UART_BAUDRATE_BAUDRATE_Baud2400,   /**< 2400 baud. */
    DRV_UART_CFG_BAUDRATE_4800    = UART_BAUDRATE_BAUDRATE_Baud4800,   /**< 4800 baud. */
    DRV_UART_CFG_BAUDRATE_9600    = UART_BAUDRATE_BAUDRATE_Baud9600,   /**< 9600 baud. */
    DRV_UART_CFG_BAUDRATE_14400   = UART_BAUDRATE_BAUDRATE_Baud14400,  /**< 14400 baud. */
    DRV_UART_CFG_BAUDRATE_19200   = UART_BAUDRATE_BAUDRATE_Baud19200,  /**< 19200 baud. */
    DRV_UART_CFG_BAUDRATE_28800   = UART_BAUDRATE_BAUDRATE_Baud28800,  /**< 28800 baud. */
    DRV_UART_CFG_BAUDRATE_31250   = UART_BAUDRATE_BAUDRATE_Baud31250,  /**< 31250 baud. */
    DRV_UART_CFG_BAUDRATE_38400   = UART_BAUDRATE_BAUDRATE_Baud38400,  /**< 38400 baud. */
    DRV_UART_CFG_BAUDRATE_56000   = UART_BAUDRATE_BAUDRATE_Baud56000,  /**< 56000 baud. */
    DRV_UART_CFG_BAUDRATE_57600   = UART_BAUDRATE_BAUDRATE_Baud57600,  /**< 57600 baud. */
    DRV_UART_CFG_BAUDRATE_76800   = UART_BAUDRATE_BAUDRATE_Baud76800,  /**< 76800 baud. */
    DRV_UART_CFG_BAUDRATE_115200  = UART_BAUDRATE_BAUDRATE_Baud115200, /**< 115200 baud. */
    DRV_UART_CFG_BAUDRATE_230400  = UART_BAUDRATE_BAUDRATE_Baud230400, /**< 230400 baud. */
    DRV_UART_CFG_BAUDRATE_250000  = UART_BAUDRATE_BAUDRATE_Baud250000, /**< 250000 baud. */
    DRV_UART_CFG_BAUDRATE_460800  = UART_BAUDRATE_BAUDRATE_Baud460800, /**< 460800 baud. */
    DRV_UART_CFG_BAUDRATE_921600  = UART_BAUDRATE_BAUDRATE_Baud921600, /**< 921600 baud. */
    DRV_UART_CFG_BAUDRATE_1000000 = UART_BAUDRATE_BAUDRATE_Baud1M,     /**< 1000000 baud. */
} drv_uart_cfg_baudrate_t;

/** @brief Types of UART parity modes. */
typedef enum
{
    DRV_UART_CFG_PARITY_EXCLUDED = UART_CONFIG_PARITY_Excluded << UART_CONFIG_PARITY_Pos, /**< Parity excluded. */
    DRV_UART_CFG_PARITY_INCLUDED = UART_CONFIG_PARITY_Included << UART_CONFIG_PARITY_Pos, /**< Parity included. */
} drv_uart_cfg_parity_t;

/** @brief Types of UART flow control modes. */
typedef enum
{
    DRV_UART_CFG_HWFC_DISABLED = UART_CONFIG_HWFC_Disabled, /**< Hardware flow control disabled. */
    DRV_UART_CFG_HWFC_ENABLED  = UART_CONFIG_HWFC_Enabled,  /**< Hardware flow control enabled. */
} drv_uart_cfg_hwfc_t;

/** @brief Types of UART Stopbit modes. */
typedef enum
{
    DRV_UART_CFG_STOP_BIT_ONE = UART_CONFIG_STOP_One << UART_CONFIG_STOP_Pos, /**< Stopbit control one mode. */
    DRV_UART_CFG_STOP_BIT_TWO = UART_CONFIG_STOP_Two << UART_CONFIG_STOP_Pos,  /**< Stopbit control two mode. */
} drv_uart_cfg_stop_bit_t;

/*_______________________________________________________________________________________*/
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

/*_______________________________________________________________________________________*/
/* UART EVENT */
typedef enum
{
    DRV_UART_EVENT_RXDRDY = UART_INTENSET_RXDRDY_Set << UART_INTENSET_RXDRDY_Pos, /**< RXD ready event. */
    DRV_UART_EVENT_TXDRDY = UART_INTENSET_TXDRDY_Set << UART_INTENSET_TXDRDY_Pos, /**< TXD ready event. */
} drv_uart_event_t;

typedef struct DRV_UART_s
{
    NRF_UART_Type* reg;                     /* Register address */
    drv_uart_cfg_baudrate_t baudrate;           /* Baudrate */
    drv_uart_cfg_hwfc_t  hwfc;                  /* Hardware flow control */
    drv_uart_cfg_parity_t  parity;              /* Parity */
    drv_uart_cfg_stop_bit_t  stopbits;          /* Stop bits */
    uint32_t tx_pin;                        /* Tx pin number */
    uint32_t rx_pin;                        /* Rx pin number */
    uint32_t cts_pin;                       /* Cts pin number */ 
    uint32_t rts_pin;                       /* Rts pin number */
}drv_uart_t, *drv_uart_p;

#define DRV_UART_DEFAULT_CONFIG { \
    .reg = NRF_UART0, \
    .baudrate = DRV_UART_CFG_BAUDRATE_115200, \
    .hwfc = DRV_UART_CFG_HWFC_DISABLED, \
    .parity = DRV_UART_CFG_PARITY_EXCLUDED, \
    .stopbits = DRV_UART_CFG_STOP_BIT_ONE, \
    .tx_pin = DRV_UART_PSEL_DISCONNECTED, \
    .rx_pin = DRV_UART_PSEL_DISCONNECTED, \
    .cts_pin = DRV_UART_PSEL_DISCONNECTED, \
    .rts_pin = DRV_UART_PSEL_DISCONNECTED, \
}


DRV_STA_t drv_uart_init(drv_uart_t* drv);
DRV_STA_t drv_uart_deinit(drv_uart_t* drv);
DRV_STA_t drv_uart_config(drv_uart_t* drv);
DRV_STA_t drv_uart_send(drv_uart_t* drv, uint8_t* data, uint32_t len);
DRV_STA_t drv_uart_send_byte(drv_uart_t* drv, uint8_t data);

#ifdef __cplusplus
}
#endif
#endif

