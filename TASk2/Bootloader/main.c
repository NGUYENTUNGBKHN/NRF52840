#include <stdint.h>
#include "log.h"
#include "memory_map.h"

static void jump_app();
static void jump_boot();


// uint32_t *activates(uint32_t *stack);
// void syscall(void);

// void task1(void)
// {
//     logPrintf("usertask : 1st call of userstask! \n");
//     logPrintf("usertask : Now, return to kernel mode \n");
//     syscall();
//     logPrintf("usertask : 2nd call of userstask! \n");
//     logPrintf("usertask : Now, return to kernel mode \n");
//     syscall();
//     while (1)
//     {
        
//     }
// }

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

    /* Change vector table */
    SCB->VTOR = 0x000E0000;

    reset_handler();
}

static void jump_boot()
{
    // uint32_t userTask_stack[256];
    // uint32_t *usertask_stack_start = userTask_stack + 256 - 16;
    // usertask_stack_start[8] = (uint32_t) &task1;

    // logPrintf("OS : Calling the usertask (1st time)\n");
    // usertask_stack_start = activates(usertask_stack_start);
    // logPrintf("OS : Return to the OS mode\n");
    // logPrintf("OS : Calling the usertask (2nd time)\n");
    // usertask_stack_start = activates(usertask_stack_start);
    // logPrintf("OS : Return the OS mode \n");
    // logPrintf("OS : Going to infinite loop ... \n");
}
