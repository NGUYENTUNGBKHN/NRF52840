/******************************************************************************/
/*! @addtogroup Group2
    @file       download.c
    @brief      
    @date       2025/06/06
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#include "download.h"
#include "drv_uarte.h"
#include "hal_nvmc.h"
#include "Trace/ace_trace.h"

#define DL_HEADER_DATA 0x24

#define DL_INFO     0x30
#define DL_ERASE    0x31
#define DL_WRTIE    0x32
#define DL_END      0x33

#define RX_BUFFER_MAX 256
#define RX_BUFEER_MASK (RX_BUFFER_MAX - 1)

static uint8_t rx_data[RX_BUFFER_MAX];
static uint8_t rx_len = 0;

static volatile uint8_t dl_state = 0;

static void donwload_analyst_data(uint8_t data)
{
    static uint8_t step = 0;
    // ace_trace_log("step = %d rx_len = %d\n",step, rx_len);
    switch (step)
    {
    case 0: // header
        /* code */
        if (data == DL_HEADER_DATA)
        {
            rx_len = 0;
            rx_data[rx_len++] = data;
            step++;
        }
        break;
    case 1: // length
        rx_data[rx_len++] = data;
        step ++;
        break;
    case 2: // cmd data
        rx_data[rx_len++] = data;
        if ((rx_len + 1) == rx_data[1])
        {
            step++;
        }
        break;
    case 3: // CRC
        rx_data[rx_len] = data;
        dl_state = rx_data[2];
        step = 0;
        break;
    default:
        break;
    }
    
}

void download_irq_handler(drv_uarte_event evt, void *p_context)
{
    uint8_t *data = (uint8_t*)p_context;
    switch (evt)
    {
    case DRV_UARTE_EVENT_RX_DONE:
        /* code */
        donwload_analyst_data(*data);
        // ace_trace_log("data = %x\n",*data);
        break;
    default:
        break;
    }
}

void download_process(drv_uarte_t *uart)
{
    uint8_t ack[4] = {0x24, 0x04, 0x00, 0x00};
    uint8_t nck[4] = {0x24, 0x04, 0x01, 0x00};
    while (1)
    {
        /* code */
        switch (dl_state)
        {
        case DL_INFO:
            break;
        case DL_ERASE:
            dl_state = 0;
            ace_trace_log("erase\n");
            hal_nvmc_page_erase(ADDR_APP_SECTION);
            uart->drv_uarte_send_data(uart, ack, 4);
            break;
        case DL_WRTIE:
            dl_state = 0;
            ace_trace_log("write = %x\n", rx_data[3]);
            hal_nvmc_write_byte(ADDR_APP_SECTION, rx_data[3]);
            uart->drv_uarte_send_data(uart, ack, 4);
            break;
        case DL_END:
            dl_state = 0;
            ace_trace_log("end\n");
            uart->drv_uarte_send_data(uart, ack, 4);
            __disable_irq();
            NVIC_SystemReset();
            break;
        default:
            // dl_state = 0;
            break;
        }
    }
    
}

void download_init()
{
    drv_uarte_t *uart0 = drv_uarte_create(0);
    uart0->drv_uarte_config(uart0, download_irq_handler);
    uart0->drv_uarte_received(uart0, 0);
    download_process(uart0);
}



