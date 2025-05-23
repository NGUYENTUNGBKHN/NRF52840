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
void RADIO_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void UARTE0_UART0_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void NFCT_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void GPIOTE_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void SAADC_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void TIMER0_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void TIMER1_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void TIMER2_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void RTC0_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void TEMP_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void RNG_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void ECB_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void CCM_AAR_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void WDT_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void RTC1_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void QDEC_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void COMP_LPCOMP_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void SWI0_EGU0_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void SWI1_EGU1_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void SWI2_EGU2_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void SWI3_EGU3_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void SWI4_EGU4_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void SWI5_EGU5_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void TIMER3_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void TIMER4_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void PWM0_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void PDM_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void MWU_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void PWM1_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void PWM2_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void SPIM2_SPIS2_SPI2_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void PWM2_IRQHRTC2_IRQHandlerandler(void) __attribute((weak, alias("empty_handler")));
void RTC2_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void I2S_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void FPU_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void USBD_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void UARTE1_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void QSPI_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void CRYPTOCELL_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void PWM3_IRQHandler(void) __attribute((weak, alias("empty_handler")));
void SPIM3_IRQHandler(void) __attribute((weak, alias("empty_handler")));


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
    (uint32_t*) SVC_Handler,                                        /* SVCall handler */
    0,
    0,
    (uint32_t*) PendSV_Handler,                                     /* -2. PendSV handler */
    (uint32_t*) SysTick_Handler,                                    /* -1. SysTick handler */
    /* External interrupts */
    (uint32_t*) POWER_CLOCK_IRQHandler,                             /* 0. Power & clock handler */
    (uint32_t*) RADIO_IRQHandler,                                   /* 1. Radio handler */
    (uint32_t*) UARTE0_UART0_IRQHandler,                            /* 2. Uart0 uarte0 handler */
    (uint32_t*) SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler,
    (uint32_t*) SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler,
    (uint32_t*) NFCT_IRQHandler,
    (uint32_t*) GPIOTE_IRQHandler,
    (uint32_t*) SAADC_IRQHandler,
    (uint32_t*) TIMER0_IRQHandler,
    (uint32_t*) TIMER1_IRQHandler,
    (uint32_t*) TIMER2_IRQHandler,
    (uint32_t*) RTC0_IRQHandler,
    (uint32_t*) TEMP_IRQHandler,
    (uint32_t*) RNG_IRQHandler,
    (uint32_t*) ECB_IRQHandler,
    (uint32_t*) CCM_AAR_IRQHandler,
    (uint32_t*) WDT_IRQHandler,
    (uint32_t*) RTC1_IRQHandler,
    (uint32_t*) QDEC_IRQHandler,
    (uint32_t*) COMP_LPCOMP_IRQHandler,
    (uint32_t*) SWI0_EGU0_IRQHandler,
    (uint32_t*) SWI1_EGU1_IRQHandler,
    (uint32_t*) SWI2_EGU2_IRQHandler,
    (uint32_t*) SWI3_EGU3_IRQHandler,
    (uint32_t*) SWI4_EGU4_IRQHandler,
    (uint32_t*) SWI5_EGU5_IRQHandler,
    (uint32_t*) TIMER3_IRQHandler,
    (uint32_t*) TIMER4_IRQHandler,
    (uint32_t*) PWM0_IRQHandler,
    (uint32_t*) PDM_IRQHandler,
    0,                       
    0,                       
    (uint32_t*) MWU_IRQHandler,
    (uint32_t*) PWM1_IRQHandler,
    (uint32_t*) PWM2_IRQHandler,
    (uint32_t*) SPIM2_SPIS2_SPI2_IRQHandler,
    (uint32_t*) RTC2_IRQHandler,
    (uint32_t*) I2S_IRQHandler,
    (uint32_t*) FPU_IRQHandler,
    (uint32_t*) USBD_IRQHandler,
    (uint32_t*) UARTE1_IRQHandler,
    (uint32_t*) QSPI_IRQHandler,
    (uint32_t*) CRYPTOCELL_IRQHandler,
    0,                      
    0,                    
    (uint32_t*) PWM3_IRQHandler,
    0,                        
    (uint32_t*) SPIM3_IRQHandler,
    0,                 
    0,                 
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
    0,                   
};

