/******************************************************************************/
/*! @addtogroup Group2
    @file       main.c
    @brief      
    @date       2024/06/10
    @author     Development Dept at Tokyo
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#include <stdint.h>
#include "bare_core.h"

#define ADDR_MSP_OF_APP 0x10000000

static void jump_to_bootloader();
static void jump_to_app();

int main()
{

    uint32_t switch_mode = 0;
    if (switch_mode)
    {
        jump_to_bootloader();
    }
    else
    {
        jump_to_app();
    }



    while (1)
    {
        /* code */
    }
    
    return 0;
}

static void jump_to_bootloader()
{

}


static void jump_to_app()
{
    void (*reset_handler)(void);

    uint32_t addr_msp_of_app = (*(volatile uint32_t*)(ADDR_MSP_OF_APP));

    __set_MSP(addr_msp_of_app);
    reset_handler = (void*)(*(volatile uint32_t*)ADDR_MSP_OF_APP);

    reset_handler();
}
