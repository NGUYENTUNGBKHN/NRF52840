#include "main.h"
static void jump_boot();
static void jump_app();

int main()
{
    volatile static uint32_t count = 0;
    logInit();
    ace_trace_init();
    ace_trace_log("ACE Bootloader\n");
    logPrintf("ACE Bootloader\n");
    
    if (1)
    {
        ace_trace_log("Jump to Application\n");
        logPrintf("Jump to Application\n");
        //jump_app();
    }
    else
    {
        ace_trace_log("Jump to Bootloader\n");
        logPrintf("Jump to Bootloader\n");
        //jump_boot();
    }

    while (1)
    {
        /* code */

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
    // bootloader();
}
