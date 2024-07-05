/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_uart.c
    @brief      
    @date       2024/06/19
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#include <stdlib.h> 
#include "drv_uart.h"

#define DRV_UART_MAX_BUFF 256
#define RX_PIN_NUMBER 8
#define TX_PIN_NUMBER 6
#define CTS_PIN_NUMBER 7
#define RTS_PIN_NUMBER 5
#define PORT0 0

/******************************************************************************/
/* Constructor
    @brief    Contructor uart  
    
    @param self 
    @param send 
    @param received 
    @param config 
    @param send_buff_size 
    @param received_buff_size 
******************************************************************************/
static void drv_uart_init(drv_uart_t* const self,
                    uint32_t (*send)(drv_uart_t* const self),
                    uint32_t (*received)(drv_uart_t* const self),
                    uint32_t (*config)(drv_uart_t* const self),
                    uint32_t send_buff_size,
                    uint32_t received_buff_size)
{
    self->instance = uart0;
    self->send = send;
    self->received = received;
    self->config = config;
    self->send_size = send_buff_size;
    self->received_size = received_buff_size;
    self->status = DRV_UART_INIT;
    self->send_buffer = (uint8_t*)malloc(send_buff_size*sizeof(uint8_t*)); 
    self->receive_buffer = (uint8_t*)malloc(received_buff_size*sizeof(uint8_t*));
}

uint32_t drv_uart_send(drv_uart_t* const self)
{
    for(uint16_t index; index < self->send_size; index++)
    {
        self->instance->TXD = self->send_buffer[index];
        
    }
    return 0;    
}

uint32_t drv_uart_received(drv_uart_t* const self)
{
    return 0;
}

uint32_t drv_uart_config(drv_uart_t* const self)
{
    self->instance->BAUDRATE = UART_BAUDRATE_115200;                    /* 115200 baud */
    self->instance->CONFIG = UART_CONFIG_HWFC_DIS |                     /* hard flow off */
                            UART_CONFIG_PARITY_EXE |                    /* parity exc */
                            UART_CONFIG_STOP_ONE ;                      /* stop bit one */
    self->instance->ENABLE = UART_ENABLE_REGISTER_EN;                   /* enable uart */
    self->instance->PSEL_RXD = UART_RXD_CONNECT | 
                            (PORT0 << UART_RXD_PORT_POS) | 
                            (RX_PIN_NUMBER << UART_RXD_PIN_POS);
    self->instance->PSEL_TXD = UART_TXD_CONNECT |
                            (PORT0 << UART_TXD_PORT_POS) | 
                            (TX_PIN_NUMBER << UART_TXD_PIN_POS);
    
    /* interrupt */
    self->instance->INTENSET = UART_INTENSET_TXDRDY_EN;
    self->instance->TASKS_STARTTX = 0x01;
    
    return 0;
}

drv_uart_t* drv_uart_create()
{
    drv_uart_t* self = (drv_uart_t*)malloc(sizeof(drv_uart_t));
    if (self == NULL)
    {
        return NULL;
    }

    drv_uart_init(self,
                drv_uart_send,
                drv_uart_received,
                drv_uart_config,
                DRV_UART_MAX_BUFF,
                DRV_UART_MAX_BUFF);
    return self;
}

void drv_uart_deinit(drv_uart_t* const self)
{
    if (self != NULL)
    {
        free(self->send_buffer);
        free(self->received);
        free(self);
    }
}
