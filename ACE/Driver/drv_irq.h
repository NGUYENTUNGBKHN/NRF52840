/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_irq.h
    @brief      
    @date       2025/04/30
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _DRV_IRQ_H_
#define _DRV_IRQ_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */

// SYSTICK
#define drv_systick_handler         SysTick_Handler
// POWER_CLOCK_IRQn
#define drv_power_clock_irq_handler    POWER_CLOCK_IRQHandler
// RADIO 
#define drv_radio_irq_handler          RADIO_IRQHandler
// UART
// #define drv_uart_irq_handler            UARTE0_UART0_IRQHandler
#define drv_uarte_irq_handler           UARTE0_UART0_IRQHandler
// UARTE

#ifdef __cplusplus
}
#endif
#endif
