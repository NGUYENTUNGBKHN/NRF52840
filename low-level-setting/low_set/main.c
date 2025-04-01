#include <stdint.h>
#include "log.h"

void delay(volatile uint32_t count);

__attribute((section(".custom_ram_block")))
unsigned char custom_ram_block[10];

__attribute((section(".custom_flash_block")))
unsigned char custom_flash_block[10];

int main()
{
    logInit();
    logPrintf("Low level setting 1\n");
    custom_flash_block[0] = 0x12;
    custom_flash_block[1] = 0x34;
    custom_ram_block[0] = 0x56;
    custom_ram_block[1] = 0x78;
    while (1)
    {
        // delay(1000000);
        /* code */
        // logPrintf("Test \n");
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
