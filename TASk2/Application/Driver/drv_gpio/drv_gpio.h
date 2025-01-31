/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_gpio.h
    @brief      
    @date       2024/12/17
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#ifndef _DRV_GPIO_H_
#define _DRV_GPIO_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include "bare_core/core.h"
#include "Inc_common/reg.h"


#define drv_gpio_map(port, pin) ((port << 5) | (pin & 0x1F))
#define P0_PIN_NUM  drv_gpio_map(0, 32)

typedef enum
{
    DRV_GPIO_PIN_DIR_INPUT  = GPIO_CNF_CONFIG_DIR_INPUT,
    DRV_GPIO_PIN_DIR_OUTPUT = GPIO_CNF_CONFIG_DIR_OUTPUT
}drv_gpio_pin_dir_t;

typedef enum
{
    DRV_GPIO_PIN_INPUT_CON = GPIO_CNF_CONFIG_IN_CONNECT,
    DRV_GPIO_PIN_INPUT_DIS = GPIO_CNF_CONFIG_IN_DISCONNECT
}drv_gpio_pin_input_t;

typedef enum
{
    DRV_GPIO_PIN_PULL_DIS   = GPIO_CNF_CONFIG_PULL_DIS,
    DRV_GPIO_PIN_PULL_DOWN  = GPIO_CNF_CONFIG_PULL_DOWN,
    DRV_GPIO_PIN_PULL_UP    = GPIO_CNF_CONFIG_PULL_UP
}drv_gpio_pin_pull_t;

typedef enum
{
    DRV_GPIO_PIN_DRIVE_S0S1 = GPIO_CNF_CONFIG_DRIVE_S0S1,
    DRV_GPIO_PIN_DRIVE_H0S1 = GPIO_CNF_CONFIG_DRIVE_H0S1,
    DRV_GPIO_PIN_DRIVE_S0H1 = GPIO_CNF_CONFIG_DRIVE_S0H1,
    DRV_GPIO_PIN_DRIVE_H0H1 = GPIO_CNF_CONFIG_DRIVE_H0H1,
    DRV_GPIO_PIN_DRIVE_D0S1 = GPIO_CNF_CONFIG_DRIVE_D0S1,
    DRV_GPIO_PIN_DRIVE_D0H1 = GPIO_CNF_CONFIG_DRIVE_D0H1,
    DRV_GPIO_PIN_DRIVE_S0D1 = GPIO_CNF_CONFIG_DRIVE_S0D1,
    DRV_GPIO_PIN_DRIVE_H0H1 = GPIO_CNF_CONFIG_DRIVE_H0H1
}drv_gpio_pin_drive_t;

typedef enum
{
    DRV_GPIO_PIN_SENSE_DIS  = GPIO_CNF_CONFIG_SENSE_DIS,
    DRV_GPIO_PIN_SENSE_HIGH = GPIO_CNF_CONFIG_SENSE_HIGH,
    DRV_GPIO_PIN_SENSE_LOW  = GPIO_CNF_CONFIG_SENSE_LOW
}drv_gpio_pin_sense_t;


__STATIC_INLINE Gpio_type_t *drv_gpio_pin_port_decode(uint32_t *p_pin)
{
    /* check pin use assert */
    if (p_pin < P0_PIN_NUM)
    {
        return gpio0;
    }
    else
    {
        *p_pin = *p_pin & 0x1F;
        return gpio1;
    }
}

__STATIC_INLINE void drv_gpio_cfg(uint32_t pin_no,
                                drv_gpio_pin_dir_t pin_dir,
                                drv_gpio_pin_input_t pin_input,
                                drv_gpio_pin_pull_t pin_pull,
                                drv_gpio_pin_drive_t pin_drive,
                                drv_gpio_pin_sense_t pin_sense)
{
    Gpio_type_t *reg = drv_gpio_pin_port_decode(&pin_no);

    reg->PIN_CNF[pin_no] = ((uint32_t)pin_dir)
                            | ((uint32_t)pin_pull)
                            | ((uint32_t)pin_drive)
                            | ((uint32_t)pin_sense)
                            | ((uint32_t)pin_dir);
}

__STATIC_INLINE void drv_gpio_cfg_output(uint32_t pin_no)
{
    drv_gpio_cfg(pin_no,
                DRV_GPIO_PIN_DIR_OUTPUT,
                DRV_GPIO_PIN_INPUT_DIS,
                DRV_GPIO_PIN_PULL_DIS,
                DRV_GPIO_PIN_DRIVE_S0S1,
                DRV_GPIO_PIN_SENSE_DIS);
}

__STATIC_INLINE void drv_gpio_cfg_input(uint32_t pin_no, drv_gpio_pin_pull_t pull_cfg)
{
    drv_gpio_cfg(pin_no,
                DRV_GPIO_PIN_DIR_INPUT,
                DRV_GPIO_PIN_INPUT_CON,
                pull_cfg,
                DRV_GPIO_PIN_DRIVE_S0S1,
                DRV_GPIO_PIN_SENSE_DIS);
}

__STATIC_INLINE uint32_t drv_gpio_port_in_read(Gpio_type_t *p_reg)
{
    return p_reg->IN;
}

__STATIC_INLINE uint32_t drv_gpio_port_dir_read(Gpio_type_t *p_reg)
{
    return p_reg->DIR;
}

__STATIC_INLINE uint32_t drv_gpio_port_in_read(Gpio_type_t *p_reg)
{
    return p_reg->IN;
}

__STATIC_INLINE uint32_t drv_gpio_port_out_read(Gpio_type_t *p_reg)
{
    return p_reg->OUT;
}

__STATIC_INLINE void drv_gpio_port_out_write(Gpio_type_t *p_reg, uint32_t value)
{
    p_reg->OUT = value;
}

__STATIC_INLINE void drv_gpio_port_out_set(Gpio_type_t *p_reg, uint32_t set_mask)
{
    p_reg->OUTSET = set_mask;
}

__STATIC_INLINE void drv_gpio_port_out_clear(Gpio_type_t *p_reg, uint32_t clr_mask)
{
    p_reg->OUTCLR = clr_mask;
}

typedef void *config(drv_gpio_t gpio,
                    drv_gpio_pin_dir_t pin_dir,
                    drv_gpio_pin_input_t pin_input,
                    drv_gpio_pin_pull_t pin_pull,
                    drv_gpio_pin_drive_t pin_drive,
                    drv_gpio_pin_sense_t pin_sense);

typedef void *set_dir(drv_gpio_t gpio, uint32_t dir);

typedef void *output(drv_gpio_t gpio, uint32_t value);

typedef uint32_t *input(drv_gpio_t gpio);

typedef struct drv_gpio_s
{
    uint32_t pin_no;
    uint32_t pin_dir;
    uint32_t pin_input;
    uint32_t pin_pull;
    uint32_t pin_drive;
    uint32_t pin_sense;
    config *gpio_config;
    set_dir *gpio_set_dir;
    output *gpio_output;
    input *gpio_input;
}drv_gpio_t, *drv_gpio_p;

extern void drv_gpio_init(drv_gpio_t* const self,
                        config *gpio_config,
                        set_dir *gpio_set_dir,
                        output *gpio_output,
                        input *gpio_input);

#ifdef __cplusplus
}
#endif
#endif


