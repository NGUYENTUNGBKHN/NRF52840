#include <stdint.h>
#include <stdio.h>

void delay(volatile uint32_t count);

void ITM_init()
{
//     // step 2
// 	NRF_CLOCK->TRACECONFIG = (NRF_CLOCK->TRACECONFIG & ~CLOCK_TRACECONFIG_TRACEPORTSPEED_Msk) |
//     (CLOCK_TRACECONFIG_TRACEPORTSPEED_4MHz << CLOCK_TRACECONFIG_TRACEPORTSPEED_Pos);
// // step 3
// ITM->TCR |= 1;
// ITM->TER |= 1;
}

int main()
{
    // printf("Hello World\n");
    while (1)
    {
        delay(1000000);
        printf("Hello World\n");
    }
    
    return 0;
}

void delay(volatile uint32_t count)
{
    while (count--)
    {
        // Do nothing, just decrement the count
    }
}
