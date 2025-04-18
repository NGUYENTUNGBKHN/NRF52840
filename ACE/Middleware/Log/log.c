/******************************************************************************/
/*! @addtogroup Group2
    @file       log.c
    @brief      
    @date       2024/11/19
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#include "log.h"
#include "drv_uart.h"

drv_uart_t drv_uart;

int logPrintf(const char *str)
{
    while (*str)
    {
        /* code */
        drv_uart_send_byte(&drv_uart, *str++);
    }
    
    
    return 0;
}

void logInit()
{
    drv_uart = (drv_uart_t)DRV_UART_DEFAULT_CONFIG;
    drv_uart_config(&drv_uart);
    drv_uart_init(&drv_uart);
}
