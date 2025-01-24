/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_gpio.c
    @brief      
    @date       2024/12/17
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#include "drv_gpio.h"

static void drv_gpio_config(uint32_t pin_no,
                    drv_gpio_pin_dir_t pin_dir,
                    drv_gpio_pin_input_t pin_input,
                    drv_gpio_pin_pull_t pin_pull,
                    drv_gpio_pin_drive_t pin_drive,
                    drv_gpio_pin_sense_t pin_sense)
{

}

static void drv_gpio_set_dir(drv_gpio_t *self)
{

}

static void drv_gpio_out(drv_gpio_t *self)
{

}

static uint32_t drv_gpio_input()
{

    return ;
}

drv_gpio_t* drv_gpio_init(drv_gpio_t *self, uint32_t pin_no)
{
    drv_gpio_t *drv_gpio = malloc(sizeof(drv_gpio_t*));

    drv_gpio->pin_no = pin_no;
    drv_gpio->gpio_config = drv_gpio_config;
    drv_gpio->gpio_set_dir = drv_gpio_set_dir;
    drv_gpio->gpio_output = drv_gpio_out;
    drv_gpio->gpio_input = drv_gpio_input;
}
