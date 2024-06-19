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
    self->send = send;
    self->received = received;
    self->config = config;
    self->status = DRV_UART_INIT;
    self->send_buffer = (uint8_t*)malloc(send_buff_size*sizeof(uint8_t*)); 
    self->receive_buffer = (uint8_t*)malloc(received_buff_size*sizeof(uint8_t*));
}

uint32_t drv_uart_send(drv_uart_t* const self)
{
    return 0;    
}

uint32_t drv_uart_received(drv_uart_t* const self)
{
    return 0;
}

uint32_t drv_uart_config(drv_uart_t* const self)
{
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
