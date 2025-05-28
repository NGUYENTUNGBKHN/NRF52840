/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_uart.c
    @brief      
    @date       2025/05/23
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#include "drv_uart.h"
#include "Trace/ace_trace.h"
#include "drv_irq.h"

#define RX_PIN_NUMBER 8
#define TX_PIN_NUMBER 6
#define CTS_PIN_NUMBER 7
#define RTS_PIN_NUMBER 5
#define PORT0 0

static drv_uart_t m_drv_uart0 = {0};
volatile static uint8_t drv_uart_tx_flag_done = 0;
volatile static uint8_t drv_uart_rx_timeout = 0;

static drv_uart_ring_buffer_t drv_uart_ring_buffer; 

static void drv_uart_irq_enable()
{
    uint8_t priority = 4;
    /* Check irq enable ? */
    if (!DRV_IRQ_IS_ENABLED(DRV_IRQ_NUMBER_GET(m_drv_uart0.reg)))
    {
        DRV_IRQ_PRIORITY_SET(DRV_IRQ_NUMBER_GET(m_drv_uart0.reg), priority);
        DRV_IRQ_ENABLE(DRV_IRQ_NUMBER_GET(m_drv_uart0.reg));
    }
}

static void drv_uart_irq_disable()
{
    /* Check irq enable ? */
    if (DRV_IRQ_IS_ENABLED(DRV_IRQ_NUMBER_GET(m_drv_uart0.reg)))
    {
        DRV_IRQ_DISABLE(DRV_IRQ_NUMBER_GET(m_drv_uart0.reg));
    }
}

drv_sta_t drv_uart_init(uint8_t index)
{
    /* if driver uart was initialized, it will re-initialize */
    if (m_drv_uart0.drv_initialized)
    {
        return DRV_STA_NG;
    }

    if (index == 0)
    {
        m_drv_uart0 = (drv_uart_t)DRV_UART_INSTANCE0;
        m_drv_uart0.drv_initialized = 1;
        drv_uart_ring_buffer.head = 0;
        drv_uart_ring_buffer.tail = 0;
    }
    else
    {
        return DRV_STA_NG;
    }
    return DRV_STA_OK;
}

drv_sta_t drv_uart_config(drv_uart_handler_t func)
{
    if (!m_drv_uart0.drv_initialized)
    {
        return DRV_STA_NG;
    }
    /* Configure gpio of UART */
    m_drv_uart0.cfg.rdx_pin = DRV_UART_PSEL_SETUP(PORT0, RX_PIN_NUMBER);
    m_drv_uart0.cfg.tdx_pin = DRV_UART_PSEL_SETUP(PORT0, TX_PIN_NUMBER);

    m_drv_uart0.cfg.func = func;

    hal_uart_configure(m_drv_uart0.reg, m_drv_uart0.cfg.parity, m_drv_uart0.cfg.hwfc, m_drv_uart0.cfg.stopbit);
    hal_uart_baudrate_set(m_drv_uart0.reg, m_drv_uart0.cfg.baudrate);
    hal_uart_enable(m_drv_uart0.reg);
    hal_uart_txrx_pins_set(m_drv_uart0.reg, m_drv_uart0.cfg.tdx_pin, m_drv_uart0.cfg.rdx_pin);;

    drv_uart_irq_enable();
    return DRV_STA_OK;
}

drv_sta_t drv_uart_deinit()
{
    drv_uart_irq_disable();
    return DRV_STA_OK;
}

drv_sta_t drv_uart_send_data_it(uint8_t *data, uint16_t len)
{
    if (!m_drv_uart0.drv_initialized)
    {
        return DRV_STA_NG;
    }
    if ((m_drv_uart0.cfg.func == NULL) && !hal_uart_int_enable_check(m_drv_uart0.reg, HAL_UART_INT_MASK_TXDRDY))
    {
        return DRV_STA_NG;
    }
    /* interrupt */
    hal_uart_int_enable(m_drv_uart0.reg, HAL_UART_INT_MASK_TXDRDY);
    /* Triggger tx */
    hal_uart_task_trigger(m_drv_uart0.reg, HAL_UART_TASK_STARTTX);
    
    for (int i = 0; i < len; i++)
    {
        drv_uart_ring_buffer.data[drv_uart_ring_buffer.head] = data[i];
        drv_uart_ring_buffer.head++;
    }
    
    hal_uart_txd_set(m_drv_uart0.reg, drv_uart_ring_buffer.data[drv_uart_ring_buffer.tail]);
    drv_uart_ring_buffer.tail++;

    return DRV_STA_OK;
}

drv_sta_t drv_uart_send_data(uint8_t *data, uint16_t len)
{
    if (!m_drv_uart0.drv_initialized)
    {
        return DRV_STA_NG;
    }
    if ((m_drv_uart0.cfg.func == NULL) && !hal_uart_int_enable_check(m_drv_uart0.reg, HAL_UART_INT_MASK_TXDRDY))
    {
        /* Triggger tx */
        hal_uart_task_trigger(m_drv_uart0.reg, HAL_UART_TASK_STARTTX);
        /* Start Tx */
        for (int i = 0; i < len; i++)
        {
            /* Set tx */
            hal_uart_txd_set(m_drv_uart0.reg, data[i]);
            /* Wait event tx ready done */
            while (!hal_uart_event_check(m_drv_uart0.reg, HAL_UART_EVENT_TXDRDY)) {}
            /* Clear event tx ready */
            hal_uart_event_clear(m_drv_uart0.reg, HAL_UART_EVENT_TXDRDY);
        }
        
        /* Stop Tx */
        hal_uart_task_trigger(m_drv_uart0.reg, HAL_UART_TASK_STOPTX);
        return DRV_STA_OK;
    }
    
    return DRV_STA_NG;
}

drv_sta_t drv_uart_received_polling(uint8_t *data, uint32_t len)
{
    uint8_t i = 0;
    if (!m_drv_uart0.drv_initialized)
    {
        return DRV_STA_NG;
    }
    
    if ((m_drv_uart0.cfg.func == NULL) && !hal_uart_int_enable_check(m_drv_uart0.reg, HAL_UART_INT_MASK_RXDRDY))
    {
        /* Clear flag event rx ready */
        hal_uart_event_clear(m_drv_uart0.reg, HAL_UART_EVENT_RXDRDY);
        /* Trigger rx */
        hal_uart_task_trigger(m_drv_uart0.reg, HAL_UART_TASK_STARTRX);
        /* code */
        while(!hal_uart_event_check(m_drv_uart0.reg, HAL_UART_EVENT_RXDRDY)){}
        data[i] = hal_uart_rxd_get(m_drv_uart0.reg);
        i++;
        hal_uart_event_clear(m_drv_uart0.reg, HAL_UART_EVENT_RXDRDY);

        hal_uart_task_trigger(m_drv_uart0.reg, HAL_UART_TASK_STOPRX);
    }
    

    return DRV_STA_OK;
}

drv_sta_t drv_uart_irq_handler(void)
{
    if (hal_uart_event_check(m_drv_uart0.reg, HAL_UART_EVENT_RXDRDY))
    {
        hal_uart_event_clear(m_drv_uart0.reg, HAL_UART_EVENT_RXDRDY);
        if (m_drv_uart0.cfg.func != NULL)
        {
            m_drv_uart0.cfg.func(DRV_UART_EVENT_RX_DONE, NULL);
        }
    }

    if (hal_uart_event_check(m_drv_uart0.reg, HAL_UART_EVENT_TXDRDY))
    {
        hal_uart_event_clear(m_drv_uart0.reg, HAL_UART_EVENT_TXDRDY);
        if (m_drv_uart0.cfg.func != NULL)
        {
            m_drv_uart0.cfg.func(DRV_UART_EVENT_TX_DONE, NULL);
        }
        
        if (!((drv_uart_ring_buffer.tail&DRV_UART_BUFEER_MASK) == (drv_uart_ring_buffer.head&DRV_UART_BUFEER_MASK)))
        {
            hal_uart_txd_set(m_drv_uart0.reg, drv_uart_ring_buffer.data[drv_uart_ring_buffer.tail]);
            drv_uart_ring_buffer.tail++;
        }
        else
        {
            hal_uart_int_disable(m_drv_uart0.reg, HAL_UART_INT_MASK_TXDRDY);
            hal_uart_task_trigger(m_drv_uart0.reg, HAL_UART_TASK_STOPTX);
        }
    }
    return DRV_STA_OK;
}
