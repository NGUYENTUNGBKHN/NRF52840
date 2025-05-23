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
    }
    else
    {
        return DRV_STA_NG;
    }
    return DRV_STA_OK;
}

drv_sta_t drv_uart_config(drv_uart_handler_t func)
{
    if ((m_drv_uart0.drv_initialized != 0) || (m_drv_uart0.cfg.func != NULL))
    {
        return DRV_STA_NG;
    }

    if (NULL == func)
    {
        return DRV_STA_NG;
    }
    m_drv_uart0.drv_initialized = 1;
    m_drv_uart0.cfg.rdx_pin = DRV_UART_PSEL_SETUP(PORT0, RX_PIN_NUMBER);
    m_drv_uart0.cfg.tdx_pin = DRV_UART_PSEL_SETUP(PORT0, TX_PIN_NUMBER);

    m_drv_uart0.cfg.func = func;

    hal_uart_configure(m_drv_uart0.reg, m_drv_uart0.cfg.parity, m_drv_uart0.cfg.hwfc, m_drv_uart0.cfg.stopbit);
    hal_uart_baudrate_set(m_drv_uart0.reg, m_drv_uart0.cfg.baudrate);
    hal_uart_enable(m_drv_uart0.reg);
    hal_uart_txrx_pins_set(m_drv_uart0.reg, m_drv_uart0.cfg.tdx_pin, m_drv_uart0.cfg.rdx_pin);
    hal_uart_int_enable(m_drv_uart0.reg, HAL_UART_INT_MASK_RXDRDY | HAL_UART_INT_MASK_TXDRDY);
    hal_uart_task_trigger(m_drv_uart0.reg, HAL_UART_TASK_STARTTX | HAL_UART_TASK_STARTRX);
    drv_uart_irq_enable();
    return DRV_STA_OK;
}

drv_sta_t drv_uart_deinit()
{
    drv_uart_irq_disable();
    return DRV_STA_OK;
}

drv_sta_t drv_uart_send_data_byte(uint8_t data)
{
    if (!m_drv_uart0.drv_initialized)
    {
        return DRV_STA_NG;
    }
    drv_uart_tx_flag_done = 1;
    hal_uart_txd_set(m_drv_uart0.reg, data);
    while (drv_uart_tx_flag_done)
    {
        /* code */
    }
    

    return DRV_STA_OK;
}

drv_sta_t drv_uart_received(uint8_t data)
{
    if (!m_drv_uart0.drv_initialized)
    {
        return DRV_STA_NG;
    }

    data = hal_uart_rxd_get(m_drv_uart0.reg);
    return DRV_STA_OK;
}

drv_sta_t drv_uart_irq_handler(void)
{
    if (hal_uart_event_check(m_drv_uart0.reg, HAL_UART_EVENT_RXDRDY))
    {
        
        hal_uart_event_clear(m_drv_uart0.reg, HAL_UART_EVENT_RXDRDY);
        m_drv_uart0.cfg.func(DRV_UART_EVENT_RX_DONE, NULL);
    }

    if (hal_uart_event_check(m_drv_uart0.reg, HAL_UART_EVENT_TXDRDY))
    {
        drv_uart_tx_flag_done = 0;
        hal_uart_event_clear(m_drv_uart0.reg, HAL_UART_EVENT_TXDRDY);
        m_drv_uart0.cfg.func(DRV_UART_EVENT_TX_DONE, NULL);
    }

    return DRV_STA_OK;
}
