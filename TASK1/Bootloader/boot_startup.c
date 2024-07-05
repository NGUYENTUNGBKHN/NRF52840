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

void default_handler()
{
    while (1)
    {
        /* code */
    }
}

void MemoryManaFault_Handler(void) __attribute((weak, alias("default_handler")));
void BusFault_Handler(void) __attribute((weak, alias("default_handler")));
void UsageFault_Handler(void) __attribute((weak, alias("default_handler")));
void SVC_Handler(void) __attribute((weak, alias("default_handler")));
void DebugMon_Handler(void) __attribute((weak, alias("default_handler")));
void PendSV_Handler(void); __attribute((weak, alias("default_handler")));
void Systick_Handler(void); __attribute((weak, alias("default_handler")));

__attribute((section(".isr_vector")))
uint32_t *_isr_vector[] = 
{
    (uint32_t*)&_estack,
    (uint32_t*)Reset_Handler,
    (uint32_t*)NMI_Handler,
    (uint32_t*)HardFault_Handler,
    (uint32_t*)MemoryManaFault_Handler,
    (uint32_t*)BusFault_Handler,
    (uint32_t*)UsageFault_Handler,
    0,
    0,
    0,
    0,
    (uint32_t*)SVC_Handler,
    (uint32_t*)DebugMon_Handler,
    (uint32_t*)PendSV_Handler,
    (uint32_t*)Systick_Handler,
};

