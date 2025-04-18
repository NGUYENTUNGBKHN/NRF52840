#include <stdint.h>
#include <stdio.h>
#include "main.h"

void delay(uint32_t time)
{
    while(time--)
    {
        __asm("NOP");
    }
}

int main()
{
    uint32_t count = 0;
    // printf("hello world\n");
    ace_trace_init();
    ace_trace_log(0, "ACE Application  \n");
    logInit();
    logPrintf("ACE Application \n");
    // SEGGER_RTT_printf(0, "ACE Application %d \n",count);
    while (1)
    {
        /* code */
        ace_trace_log("Actor : NGUYEN THANH TUNG %d \n", count);
        count++;
        //SEGGER_RTT_printf(0, "ACE Application %d \n",count);
        logPrintf("ACE Application  \n");
        delay(10000000);
    }
    
    return 0;
}

