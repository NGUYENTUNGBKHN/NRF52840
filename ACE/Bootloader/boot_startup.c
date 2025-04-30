#include <stdint.h>


extern uint32_t _estack;
extern int main();


extern uint32_t _sidata;

extern uint32_t _sdata;
extern uint32_t _edata;

extern uint32_t _sbss;
extern uint32_t _ebss;

/*TRACE address*/
extern uint32_t _sram_code;
extern uint32_t _eram_code; 
extern uint32_t _ramcode_load_start;

// extern void POWER_CLOCK_IRQHandler(void);

void Reset_Handler()
{
    volatile uint32_t *start = &_sdata;
    volatile uint32_t *end = &_edata;
    volatile uint32_t *data = &_sidata;
    volatile uint32_t *bss_start = &_sbss;
    volatile uint32_t *bss_end = &_ebss;

    while (start < end)
    {
        /* code */
        *start++ = *data++;
    }
   
    /* setup bss data = 0 */
    while (bss_start < bss_end)
    {
        /* code */
        *bss_start++ = 0;
    }

    volatile uint32_t *trace_start = &_sram_code;
    volatile uint32_t *trace_end = &_eram_code; 
    volatile uint32_t *trace_data = &_ramcode_load_start;
    while (trace_start < trace_end)
    {
        /* code */
        *trace_start++ = *trace_data++;
    }

    /* Jump to __libc_init_array */
    // __libc_init_array();
    
    main();
}


void default_handler(void)
{
    while (1)
    {
        /* code */
    }
    
}

void empty_handler(void)
{
    /* code */
}

void NMI_Handler(void) __attribute((weak, alias("default_handler")));
void HardFault_Handler(void) __attribute((weak, alias("default_handler")));
void MemManage_Handler(void) __attribute((weak, alias("default_handler")));
void BusFault_Handler(void) __attribute((weak, alias("default_handler")));
void UsageFault_Handler(void) __attribute((weak, alias("default_handler")));
void SVC_Handler(void) __attribute((weak, alias("empty_handler")));
void PendSV_Handler(void) __attribute((weak, alias("empty_handler")));
void SysTick_Handler(void) __attribute((weak, alias("empty_handler")));
void POWER_CLOCK_IRQHandler(void) __attribute((weak, alias("empty_handler")));

__attribute((section(".isr_vector")))
uint32_t *_isr_vector[] = {
    (uint32_t*) &_estack,               /* top stack pointer */
    (uint32_t*) Reset_Handler,          /* Reset handler  */
    (uint32_t*) NMI_Handler,            /* NMI handler */
    (uint32_t*) HardFault_Handler,      /* Hard fault handler */
    (uint32_t*) MemManage_Handler,      /* MPU fault handler */
    (uint32_t*) BusFault_Handler,       /* Bus fault handler */
    (uint32_t*) UsageFault_Handler,     /* Usage fault handler */
    0,
    0,
    0,
    0,
    (uint32_t*) SVC_Handler,            /* SVCall handler */
    0,
    0,
    (uint32_t*) PendSV_Handler,            /* PendSV handler */
    (uint32_t*) SysTick_Handler,          /* SysTick handler */
    /* External interrupts */
    (uint32_t*) POWER_CLOCK_IRQHandler,
};

