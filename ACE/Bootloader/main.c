#include "main.h"
static void jump_boot();
static void jump_app();

uint8_t tung[2] = {0x01, 0x02};

void delay(uint32_t count)
{
    volatile uint32_t i = 0;
    for (i = 0; i < count; i++)
    {
        __asm("nop");
    }
}

int main()
{
    ace_trace_init();
    ace_trace_log("ACE Bootloader\n");
    drv_clock_init(0);
    drv_clock_enable();
    
    tung[0] = 0x06;

    if (0)
    {
        ace_trace_log("Jump to Application\n");
        jump_app();
    }
    else
    {
        ace_trace_log("Jump to Bootloader\n");
        jump_boot();
    }

    while (1)
    {
        /* code */
        ace_trace_log("Jump to Bootloader\n");
        delay(1000000);
    }
    
    return 0;
}

static void jump_app()
{
    void (*reset_handler)(void);

    uint32_t msp = *(volatile uint32_t*)ADDR_APP_BEGIN;

    uint32_t handler_address = *(volatile uint32_t*)(ADDR_APP_BEGIN + 4);

    __set_CONTROL(0x00000000);   // Set CONTROL to its reset value 0.
    __set_PRIMASK(0x00000000);   // Set PRIMASK to its reset value 0.
    __set_BASEPRI(0x00000000);   // Set BASEPRI to its reset value 0.
    __set_FAULTMASK(0x00000000); // Set FAULTMASK to its reset value 0.

    __set_MSP(msp);
    reset_handler = (void*)handler_address;

    /* Change vector table */
    SCB->VTOR = 0x000E0000;
    /* Jump to Application */
    reset_handler();
}

static void jump_boot()
{
    bootloader();
}
