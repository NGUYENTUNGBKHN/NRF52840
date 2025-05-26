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
#include "Trace/ace_trace.h"

void uart_handler(drv_uart_event evt, void *p_context)
{
    
    switch (evt)
    {
    case DRV_UART_EVENT_TX_DONE:
        // ace_trace_log("tx done\n");
        break;
    case DRV_UART_EVENT_RX_DONE:
        // ace_trace_log("rx done\n");
        break;
    default:
        break;
    }
}

int logPrintf(const char *str)
{
    while (*str)
    {
        /* code */
        drv_uart_send_data_byte(*str++);
    }

    return 0;
}

void logInit()
{
    drv_uart_init(0);
    drv_uart_config(&uart_handler);
}
