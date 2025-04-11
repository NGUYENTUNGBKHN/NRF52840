#include <stdint.h>
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
    // printf("hello world\n");
    ace_trace_init();
    ace_trace_log("Welcome Application 2 \n");
    ace_trace_log("Actor : NGUYEN THANH TUNG \n");
    // logPrintf("ACE Application 2 \n");

    while (1)
    {
        /* code */
        ace_trace_log("Actor : NGUYEN THANH TUNG \n");
    }
    
    return 0;
}

