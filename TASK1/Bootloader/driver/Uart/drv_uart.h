/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_uart.h
    @brief      
    @date       2024/06/19
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

#include "common.h"

/* CODE */
typedef struct UartType_s
{
    __OM  uint32_t TASKS_STARTRX;     /* Start UART receiver */
    __OM  uint32_t TASKS_STOPRX;      /* Stop UART receviver */
    __OM  uint32_t TASKS_STARTTX;     /* Start UART transmitter */
    __OM  uint32_t TASKS_STOPTX;      /* Stop UART transmitter */
    __IM  uint32_t RESERVED[3];       /*  */
    __OM  uint32_t TASKS_SUSPEND;     /* Suspend UART */
    __IM  uint32_t RESERVED1[56];
    __IOM uint32_t EVENTS_CTS;        /* CTS is activated (set low). Clear to Send. */
    __IOM uint32_t EVENTS_NCTS;       /* CTS is deactivated (set high). Not Clear to Send. */
    __IOM uint32_t EVENTS_RXDRDY;     /* Data received in RXD */
    __IM  uint32_t RESERVED2[4];
    __IOM uint32_t EVENTS_TXDRDY;     /* Data sent from TXD */
    __IM  uint32_t RESERVED3;
    __IOM uint32_t EVENTS_ERROR;      /* Error detected */
    __IM  uint32_t RESERVED4[7];
    __IOM uint32_t EVENTS_RXTO;       /* Receiver timeout */
    __IM  uint32_t RESERVED5[46];
    __IOM uint32_t SHORTS;            /* Shortcuts between local events and tasks */
    __IM  uint32_t RESERVED6[64];
    __IOM uint32_t INTENSET;          /* Enable interrupt */
    __IOM uint32_t INTENCLR;          /* Disable interrupt */
    __IM  uint32_t RESERVED7[93];
    __IOM uint32_t ERRORSRC;          /* Error Source */
    __IM  uint32_t RESERVED8[31];
    __IOM uint32_t ENABLE;            /* Enable UART */
    __IM  uint32_t RESERVED9;
    __IOM uint32_t PSEL_RTS;          /* Pin select for RTS */
    __IOM uint32_t PSEL_TXD;          /* Pin select for TXD */
    __IOM uint32_t PSEL_CTS;          /* Pin select for CTS */
    __IOM uint32_t PSEL_RXD;          /* Pin select for RXD */
    __IM  uint32_t RXD;               /* RXD register */
    __IOM uint32_t TXD;               /* TXD register */
    __IM  uint32_t RESERVED10;
    __IOM uint32_t BAUDRATE;          /* Baud Rate. ACCuracy depends on the HFCLK source selected */
    __IM  uint32_t RESERVED11[17];
    __IOM uint32_t CONFIG;            /* configuration of parity and hardware flow control */
}UartType_t, *UartType_p;


#define UART_CONFIG_HWFC_POS        0
#define UART_CONFIG_PARITY_POS      1
#define UART_CONFIG_STOP_POS        4 

/* interrupt */
#define UART_INTENSET_CTS_POS       0
#define UART_INTENSET_NCTS_POS      1
#define UART_INTENSET_RXDRDY_POS    2
#define UART_INTENSET_TXDRDY_POS    7
#define UART_INTENSET_ERROR_POS     9
#define UART_INTENSET_RXTO_POS      17

#define UART_INTENSET_CTS_EN        (1 << UART_INTENSET_CTS_POS)
#define UART_INTENSET_CTS_DIS       (0 << UART_INTENSET_CTS_POS)
#define UART_INTENSET_NCTS_EN       (1 << UART_INTENSET_NCTS_POS)
#define UART_INTENSET_NCTS_DIS      (0 << UART_INTENSET_NCTS_POS)
#define UART_INTENSET_RXDRDY_EN     (1 << UART_INTENSET_RXDRDY_POS)
#define UART_INTENSET_RXDRDY_DIS    (0 << UART_INTENSET_RXDRDY_POS)
#define UART_INTENSET_TXDRDY_EN     (1 << UART_INTENSET_TXDRDY_POS)
#define UART_INTENSET_TXDRDY_DIS    (0 << UART_INTENSET_TXDRDY_POS)
#define UART_INTENSET_ERROR_EN      (1 << UART_INTENSET_ERROR_POS)
#define UART_INTENSET_ERROR_DIS     (0 << UART_INTENSET_ERROR_POS)
#define UART_INTENSET_RXTO_EN       (1 << UART_INTENSET_RXTO_POS)
#define UART_INTENSET_RXTO_DIS      (0 << UART_INTENSET_RXTO_POS)

/* TXD Register */
#define UART_TXD_PIN_POS            0
#define UART_TXD_PORT_POS           5
#define UART_TXD_CONNECT_POS        31
#define UART_TXD_CONNECT            (0 << UART_TXD_CONNECT_POS)
#define UART_TXD_DISCONNECT         (1 << UART_TXD_CONNECT_POS)

/*RXD Register  */
#define UART_RXD_PIN_POS            0
#define UART_RXD_PORT_POS           5
#define UART_RXD_CONNECT_POS        31
#define UART_RXD_CONNECT            (0 << UART_RXD_CONNECT_POS)
#define UART_RXD_DISCONNECT         (1 << UART_RXD_CONNECT_POS)

/* ENABLE REGITER */
#define UART_ENABLE_REGISTER_EN     0x04
#define UART_ENABLE_REGISTER_DIS    0x00

/* BaudRate */
#define UART_BAUDRATE_1200          0x0004F000
#define UART_BAUDRATE_2400          0x0009D000
#define UART_BAUDRATE_4800          0x0009D000
#define UART_BAUDRATE_9600          0x00275000
#define UART_BAUDRATE_14400         0x003B0000
#define UART_BAUDRATE_19200         0x004EA000
#define UART_BAUDRATE_28800         0x0075F000
#define UART_BAUDRATE_31250         0x00800000
#define UART_BAUDRATE_38400         0x009D5000
#define UART_BAUDRATE_56000         0x00E50000
#define UART_BAUDRATE_57600         0x00EBF000
#define UART_BAUDRATE_76800         0x013A9000
#define UART_BAUDRATE_115200        0x01D7E000
#define UART_BAUDRATE_230400        0x03AFB000
#define UART_BAUDRATE_250000        0x04000000
#define UART_BAUDRATE_460800        0x075F7000
#define UART_BAUDRATE_921600        0x0EBED000
#define UART_BAUDRATE_1M            0x10000000



/* CONFIG REGISTER */
#define UART_CONFIG_HWFC_DIS        (0 << UART_CONFIG_HWFC_POS)
#define UART_CONFIG_HWFC_ENB        (1 << UART_CONFIG_HWFC_POS)
#define UART_CONFIG_PARITY_EXE      (0 << UART_CONFIG_PARITY_POS)
#define UART_CONFIG_PARITY_INC      (0x07 << UART_CONFIG_PARITY_POS)
#define UART_CONFIG_STOP_ONE        (0 << UART_CONFIG_STOP_POS)
#define UART_CONFIG_STOP_TWO        (1 << UART_CONFIG_STOP_POS)



#define uart0 ((UartType_t*) UART_BASE_ADDRESS)

typedef struct drv_uart_s drv_uart_t;
struct drv_uart_s
{
    /* data */
    uint8_t *send_buffer;
    uint8_t *receive_buffer;
    uint8_t status;
    /* function */
    uint32_t (*config)(drv_uart_t* const self);
    uint32_t (*send)(drv_uart_t* const self);
    uint32_t (*received)(drv_uart_t* const self);
};

enum drv_uart_status
{
    DRV_UART_INIT,
    DRV_UART_SEND,
    DRV_UART_RECEIVED,
};

#ifdef __cplusplus
}
#endif
#endif
