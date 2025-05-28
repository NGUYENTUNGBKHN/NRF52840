/******************************************************************************/
/*! @addtogroup Group2
    @file       bootloader.c
    @brief      
    @date       2025/04/28
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#include "bootloader.h"
#include "log/log.h"

void delay(uint32_t count)
{
    volatile uint32_t i = 0;
    for (i = 0; i < count; i++)
    {
        __asm("nop");
    }
}

void radio_handler(drv_radio_event_t event)
{
    switch (event)
    {
    case DRV_RADIO_EVENT_READY:
        // ace_trace_log("radio ready \n");
        break;
    case DRV_RADIO_EVENT_END:
        // ace_trace_log("radio end \n");
        break;
    case DRV_RADIO_EVENT_DISABLED:
        /* code */
        ace_trace_log("Send complete \n");
        // drv_radio_send_data();
        break;
    
    default:
        break;
    }
}

void clock_handler(drv_clock_evt_type_t event)
{
    switch (event)
    {
    case DRV_CLOCK_EVT_HFCLK_STARTED:
        /* code */
        ace_trace_log("HF enable \n");
        // logPrintf("HF enable \n");
        break;
    
    default:
        break;
    }
}

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

void bootloader()
{
    static uint8_t channel = 0;
    uint8_t data_rev;
    uint8_t data[5] = {0x31, 0x32, 0x33, 0x34, 0x35};
    ace_trace_log("Bootloader start\n");
    // logInit();
    
    while (1)
    {
        /* code */
        // Use directly __WFE and __SEV macros since the SoftDevice is not available.
        // logPrintf("hello \n");
       
        // delay(1000000);
        // Wait for event.
        // __WFE();
    }
}
