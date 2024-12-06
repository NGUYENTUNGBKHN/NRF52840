#include <stdint.h>
#include "log.h"
#include "memory_map.h"

static void jump_app();
static void jump_boot();

int main()
{

    logInit();
    logPrintf("Bootloader \n");
    logPrintf("Actor : NGUYEN THANH TUNG \n");

    if (1)
    {
        logPrintf("Jump to Application\n");
        jump_app();
    }
    else
    {
        logPrintf("Jump to Bootloader\n");
        jump_boot();
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

    reset_handler();
}

static void jump_boot()
{

}
