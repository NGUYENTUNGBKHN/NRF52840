/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_uarte.c
    @brief      
    @date       2025/05/23
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#include "drv_uarte.h"
#include "hal_uarte.h"
#include <stdlib.h>
#include "drv_irq.h"

#define RX0_PIN_NUMBER 8
#define TX0_PIN_NUMBER 6
#define CTS0_PIN_NUMBER 7
#define RTS0_PIN_NUMBER 5
#define PORT0 0

#define RX1_PIN_NUMBER 8
#define TX1_PIN_NUMBER 6
#define CTS1_PIN_NUMBER 7
#define RTS1_PIN_NUMBER 5
#define PORT1 1

static uint8_t drv_uart_intialized[2] = {0};


static void drv_uarte_irq_enable(NRF_UARTE_Type *type)
{
    uint8_t priority = 4;
    /* Check irq enable ? */
    if (!DRV_IRQ_IS_ENABLED(DRV_IRQ_NUMBER_GET(type)))
    {
        DRV_IRQ_PRIORITY_SET(DRV_IRQ_NUMBER_GET(type), priority);
        DRV_IRQ_ENABLE(DRV_IRQ_NUMBER_GET(type));
    }
}

// static void drv_uarte_irq_disable(NRF_UARTE_Type *type)
// {
//     /* Check irq enable ? */
//     if (DRV_IRQ_IS_ENABLED(DRV_IRQ_NUMBER_GET(type)))
//     {
//         DRV_IRQ_DISABLE(DRV_IRQ_NUMBER_GET(type));
//     }
// }

drv_sta_t drv_uarte_init(drv_uarte_t* const self,
                        drv_sta_t (*drv_uarte_config)(drv_uarte_t *self, drv_uarte_handler_t drv_uarte_handler),
                        drv_sta_t (*drv_uarte_send_data_it)(drv_uarte_t *self, uint8_t *data, uint32_t len),
                        drv_sta_t (*drv_uarte_send_data)(drv_uarte_t *self, uint8_t *data, uint32_t len),
                        drv_sta_t (*drv_uarte_received)(drv_uarte_t *self, uint8_t *data))
{
    if (self == NULL || drv_uarte_config == NULL || drv_uarte_send_data == NULL || drv_uarte_received == NULL || drv_uarte_send_data_it == NULL)
    {
        return DRV_STA_NG;
    }
 
    if (self->drv_index == 0)
    {
        *self = (drv_uarte_t)DRV_UARTE_INSTANCE0;
    }
    else if (self->drv_index == 1)
    {   
        *self = (drv_uarte_t)DRV_UARTE_INSTANCE1;
    }
    else
    {
        return DRV_STA_NG;
    }

    self->drv_uarte_config = drv_uarte_config;
    self->drv_uarte_send_data = drv_uarte_send_data;
    self->drv_uarte_received = drv_uarte_received;
    self->drv_uarte_send_data_it = drv_uarte_send_data_it;
    drv_uart_intialized[self->drv_index] = 1;
    return DRV_STA_OK; 
}

drv_sta_t drv_uarte_config(drv_uarte_t* const self, drv_uarte_handler_t drv_uarte_handler)
{
    if (self == NULL)
    {
        return DRV_STA_NG;
    }
    self->cfg.func = drv_uarte_handler;
    if (self->drv_index == 0)
    {
        self->cfg.rdx_pin = DRV_UARTE_PSEL_SETUP(PORT0, RX0_PIN_NUMBER);
        self->cfg.tdx_pin = DRV_UARTE_PSEL_SETUP(PORT0, TX0_PIN_NUMBER);
    }
    else if (self->drv_index == 1)
    {
        self->cfg.rdx_pin = DRV_UARTE_PSEL_SETUP(PORT1, RX1_PIN_NUMBER);
        self->cfg.rdx_pin = DRV_UARTE_PSEL_SETUP(PORT1, TX1_PIN_NUMBER);
    }
    else
    {
        return DRV_STA_NG;
    }

    hal_uarte_configure(self->reg, self->cfg.parity, self->cfg.hwfc, self->cfg.stopbit);
    hal_uarte_baudrate_set(self->reg, self->cfg.baudrate);
    hal_uarte_txrx_pins_set(self->reg, self->cfg.tdx_pin, self->cfg.rdx_pin);
    hal_uarte_enable(self->reg);
    
    drv_uarte_irq_enable(self->reg);

    return DRV_STA_OK;
}

drv_sta_t drv_uarte_send_data_it(drv_uarte_t* const self, uint8_t *data, uint32_t len)
{
    
    if (self == NULL || data == NULL)
    {
        return DRV_STA_NG;
    }
    if (self->cfg.func == NULL && !hal_uarte_int_enable_check(self->reg, HAL_UARTE_INT_TXDRDY_MASK))
    {
        return DRV_STA_NG;
    }
    hal_uarte_tx_buffer_set(self->reg, data, len);
    /* Trigger tx */
    hal_uarte_task_trigger(self->reg, HAL_UARTE_TASK_STARTTX);

    return DRV_STA_OK;
}

drv_sta_t drv_uarte_send_data(drv_uarte_t* const self, uint8_t *data, uint32_t len)
{
    if (self == NULL || data == NULL)
    {
        return DRV_STA_NG;
    }
    if (self->cfg.func == NULL && !hal_uarte_int_enable_check(self->reg, HAL_UARTE_INT_TXDRDY_MASK))
    {
        hal_uarte_tx_buffer_set(self->reg, data, len);
        /* Trigger tx */
        hal_uarte_task_trigger(self->reg, HAL_UARTE_TASK_STARTTX);
        /* Clear event */
        hal_uarte_event_clear(self->reg, HAL_UARTE_EVENT_ENDTX);

        while(!hal_uarte_event_check(self->reg, HAL_UARTE_EVENT_ENDTX)){}
        /* Clear event */
        hal_uarte_event_clear(self->reg, HAL_UARTE_EVENT_ENDTX);
        /* Stop tx */
        hal_uarte_task_trigger(self->reg, HAL_UARTE_TASK_STOPTX);
    }

    return DRV_STA_OK;
}

drv_sta_t drv_uarte_received(drv_uarte_t* const self, uint8_t *data)
{
    if (self == NULL)
    {
        return DRV_STA_NG;
    }
    return DRV_STA_OK;
}

drv_uarte_t *drv_uarte_create(uint8_t index)
{
    drv_sta_t sta;

    if (index > 1)
    {
        return NULL;
    }

    drv_uarte_t *drv_uarte = malloc(sizeof(drv_uarte_t));
    if (drv_uarte == NULL)
    {
        free(drv_uarte);
        return NULL;
    }
    
    drv_uarte->drv_index = index;
    sta = drv_uarte_init(drv_uarte,
                    drv_uarte_config,
                    drv_uarte_send_data_it,
                    drv_uarte_send_data,
                    drv_uarte_received);
    if (sta != DRV_STA_OK)
    {
        free(drv_uarte);
        return NULL;
    }

    return drv_uarte;
}


drv_sta_t drv_uarte_irq_handler()
{
    if (drv_uart_intialized[0])
    {
        if (hal_uarte_event_check(NRF_UARTE0, HAL_UARTE_EVENT_ENDTX))
        {
            hal_uarte_event_clear(NRF_UARTE0, HAL_UARTE_EVENT_ENDTX);
        }
    }
    else if (drv_uart_intialized[1])
    {
        if (hal_uarte_event_check(NRF_UARTE1, HAL_UARTE_EVENT_ENDTX))
        {
            hal_uarte_event_clear(NRF_UARTE1, HAL_UARTE_EVENT_ENDTX);
        }
    }
    return DRV_STA_OK;
}

