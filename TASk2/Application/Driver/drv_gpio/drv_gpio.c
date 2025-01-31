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

static void drv_gpio_config(drv_gpio_t* const self,
                            drv_gpio_pin_dir_t pin_dir,
                            drv_gpio_pin_input_t pin_input,
                            drv_gpio_pin_pull_t pin_pull,
                            drv_gpio_pin_drive_t pin_drive,
                            drv_gpio_pin_sense_t pin_sense)
{
    self->pin_dir = pin_dir;
    self->pin_input = pin_input;
    self->pin_pull = pin_pull;
    self->pin_drive = pin_drive;
    self->pin_sense = pin_sense;
}

static void drv_gpio_set_dir(drv_gpio_t *self)
{
    
}

static void drv_gpio_out(drv_gpio_t *self)
{

}

static uint32_t drv_gpio_input()
{

    return 1;
}

void drv_gpio_init(drv_gpio_t* const self,
                    config *gpio_config,
                    set_dir *gpio_set_dir,
                    output *gpio_output,
                    input *gpio_input)
{
    self->gpio_config = gpio_config;
    self->gpio_set_dir = gpio_set_dir;
    self->gpio_output = gpio_output;
    self->gpio_input = gpio_input;
}

drv_gpio_t* drv_gpio_create(uint32_t pin_no)
{
    drv_gpio_t* self = (drv_gpio_t*)malloc(sizeof(drv_gpio_t));

    if (self == NULL)
    {
        return NULL;
    }
    drv_gpio_init(self,
                drv_gpio_config,
                drv_gpio_set_dir,
                drv_gpio_out,
                drv_gpio_input);
    return self;
}


