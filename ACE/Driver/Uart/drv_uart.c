/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_uart.c
    @brief      
    @date       2025/04/16
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#include "drv_uart.h"
#include "string.h"
#include "nrf52840.h"
#include "drv_common.h"

#define RX_PIN_NUMBER 8
#define TX_PIN_NUMBER 6
#define CTS_PIN_NUMBER 7
#define RTS_PIN_NUMBER 5
#define PORT0 0

drv_sta_t drv_uart_init(drv_uart_t* drv)
{
    if (drv == NULL)
    {
        return DRV_STA_NG;
    }
    drv->reg->BAUDRATE = drv->baudrate;              /* 115200 baud */
    drv->reg->CONFIG = drv->hwfc |                   /* hard flow off */
                        drv->parity |                /* parity exc */
                        drv->stopbits;               /* stop bit one */
    drv->reg->ENABLE = DRV_UART_ENABLE_REGISTER_EN;   /* Enable uart  */
    drv->reg->PSEL.TXD = drv->tx_pin;      
    drv->reg->PSEL.RXD = drv->rx_pin;            
    /* Interrupt */        
    drv->reg->INTENSET = DRV_UART_EVENT_TXDRDY;      /* Enable interrupt */
    drv->reg->TASKS_STARTTX = 0x01;                  /* Start tx */
    return DRV_STA_OK;
}

drv_sta_t drv_uart_deinit(drv_uart_t* drv)
{
    if (drv == NULL)
    {
        return DRV_STA_NG;
    }
    // drv->reg->ENABLE = DRV_UART_ENABLE_REGISTER_DIS;  /* Disable uart  */
    return DRV_STA_OK;
}

drv_sta_t drv_uart_config(drv_uart_t* drv)
{
    // if (NULL != drv)
    // {
    //     return DRV_STA_NG;
    // }
    drv->tx_pin = DRV_UART_PSEL_SETUP(PORT0, TX_PIN_NUMBER);
    drv->rx_pin = DRV_UART_PSEL_SETUP(PORT0, RX_PIN_NUMBER);
    return DRV_STA_OK;
}

drv_sta_t drv_uart_send_byte(drv_uart_t* drv, uint8_t data)
{
    if (NULL == drv)
    {
        return DRV_STA_NG;
    }
    drv->reg->TXD = data; /* Send data */
    while (drv->reg->EVENTS_TXDRDY != 0x01)
    {
        /* Wait for TXDRDY event */
    }
    drv->reg->EVENTS_TXDRDY = 0x00; /* Clear TXDRDY event */
    return DRV_STA_OK;
}

drv_sta_t drv_uart_send(drv_uart_t* drv, uint8_t* data, uint32_t len)
{
    if (NULL == drv || NULL == data || len == 0)
    {
        return DRV_STA_NG;
    }
    for (uint32_t i = 0; i < len; i++)
    {
        drv->reg->TXD = data[i];
        while (drv->reg->EVENTS_TXDRDY != 0x01)
        {
            /* Wait for TXDRDY event */
        }
        drv->reg->EVENTS_TXDRDY = 0x00; /* Clear TXDRDY event */
    }
    return DRV_STA_OK;
}

