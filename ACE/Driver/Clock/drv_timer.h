/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_timer.h
    @brief      
    @date       2025/06/09
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _DRV_TIMER_H_
#define _DRV_TIMER_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include "drv_common.h"

/* CODE */
typedef enum
{
    DRV_TIMER_EVT_CP1
}drv_timer_event_t;

typedef struct drv_timer_instance_s
{
    NRF_TIMER_Type reg;
    uint8_t instance_id;
    uint8_t cc_channel_num;
}drv_timer_instance_t;

#define DRV_TIMER_INSTANCE(idx)                 \
{                                               \
    .reg = NRF_TIMER ## idx,                    \
    .instance_id = idx,                         \
    .cc_channel_num = TIMER ## idx ## _CC_NUM,  \
}

typedef struct drv_timer_config_s
{
    hal_timer_frequency_t frequency;          ///< Frequency.
    hal_timer_mode_t      mode;               ///< Mode of operation.
    hal_timer_bit_width_t bit_width;          ///< Bit width.
    uint8_t               interrupt_priority; ///< Interrupt priority.
    void *                p_context;          ///< Context passed to interrupt handler.
}drv_timer_config_t;

#define DRV_TIMER_DEFAULT_CONFIG                                                    \
{                                                                                    \
    .frequency          = (hal_timer_frequency_t)0,\
    .mode               = (hal_timer_mode_t)0,          \
    .bit_width          = (hal_timer_bit_width_t)0,\
    .interrupt_priority = 0,                    \
    .p_context          = NULL                                                       \
}

typedef void (*drv_timer_handler_t)(drv_timer_event_t event, void *p);

typedef struct drv_timer_s drv_timer_t;

struct drv_timer_s
{
    drv_timer_instance_t instance;
    drv_timer_config_t config;
    drv_timer_handler_t func;
    /* public function */
    void (*drv_timer_config)(drv_timer_t * const self, 
                            drv_timer_config_t const *cfg, 
                            drv_timer_handler_t func);
    void (*drv_timer_start)(drv_timer_t * const self, uint32_t time);
    void (*drv_timer_end)(drv_timer_t * const self);
    void (*drv_timer_is_process)(drv_timer_t * const self);
};



#ifdef __cplusplus
}
#endif
#endif
