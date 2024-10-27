#include <stdint.h>


extern uint32_t _estack;
extern int main();


extern uint32_t _sidata;

extern uint32_t _sdata;
extern uint32_t _edata;

extern uint32_t _sbss;
extern uint32_t _ebss;

void Reset_Handler()
{
    uint32_t *start;
    uint32_t *end;
    uint32_t *data;

    start = (uint32_t*)&_sdata;
    end = (uint32_t*)&_edata;
    data = (uint32_t*)&_sidata;
    /* settup initialized data */
    while (start < end)
    {
        /* code */
        *start++ = *data++;
    }
    // /* implement main function */
    start = &_sbss;
    end = &_ebss;

    /* setup bss data = 0 */
    while (start < end)
    {
        /* code */
        *start++ = 0;
    }
    

    main();
}



__attribute((section(".isr_vector")))
uint32_t *isr_vector[] = {
    (uint32_t*) &_estack,
    (uint32_t*) Reset_Handler,
    0,
};

