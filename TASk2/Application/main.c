#include <stdint.h>
#include "log.h"
#include "memory_map.h"

uint32_t *activates(uint32_t *stack);
void syscall(void);

void task1(void)
{
    logPrintf("usertask : 1st call of userstask! \n");
    logPrintf("usertask : Now, return to kernel mode \n");
    syscall();
    logPrintf("usertask : 2nd call of userstask! \n");
    logPrintf("usertask : Now, return to kernel mode \n");
    syscall();
    while (1)
    {
        
    }
}


int main()
{
    uint32_t userTask_stack[256];
    uint32_t *usertask_stack_start = userTask_stack + 256 - 16;
    usertask_stack_start[8] = (uint32_t) &task1;

    logInit();
    logPrintf("Welcome Application 2 \n");
    logPrintf("Actor : NGUYEN THANH TUNG \n");

    logPrintf("OS : Calling the usertask (1st time)\n");
    usertask_stack_start = activates(usertask_stack_start);
    logPrintf("OS : Return to the OS mode\n");
    logPrintf("OS : Calling the usertask (2nd time)\n");
    usertask_stack_start = activates(usertask_stack_start);
    logPrintf("OS : Return the OS mode \n");
    logPrintf("OS : Going to infinite loop ... \n");



    while (1)
    {
        /* code */
    }
    
    return 0;
}
