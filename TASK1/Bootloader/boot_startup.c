#include <stdint.h>

extern uint32_t _estack;
extern int main();

void Reset_Handler()
{
    main();
}

void NMI_Handler()
{
    while(1);
}

void HardFault_Handler()
{
    while(1);
}

__attribute((section(".isr_vector")))
uint32_t *_isr_vector[] = 
{
    (uint32_t*)&_estack,
    (uint32_t*)Reset_Handler,
    (uint32_t*)NMI_Handler,
    (uint32_t*)HardFault_Handler,

};

