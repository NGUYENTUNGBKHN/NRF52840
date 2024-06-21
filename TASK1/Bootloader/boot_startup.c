#include <stdint.h>

extern uint32_t s_bss;
extern uint32_t e_bss;

extern uint32_t _estack;
extern int main();

void Reset_Handler()
{

    /* Set segmment bss to 0 */
    uint32_t *bss_begin = (uint32_t*)&s_bss;
    uint32_t *bss_end = (uint32_t*)&e_bss;

    while (bss_begin < bss_end)
    {
        /* code */
        *bss_begin++ = 0; 
    }
    
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

