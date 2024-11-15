#include <stdint.h>

/* Setup variable */
extern uint32_t _estack;

extern uint32_t _sidata;

extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern int main();


void Reset_Handler()
{
    uint32_t *data;
    uint32_t *begin;
    uint32_t *end;

    data = &_sidata;
    begin = &_sdata;
    end = &_edata;

    while (begin < end)
    {
        /* code */
        *begin++ = *data++;
    }
    

    main();
}

__attribute((section(".isr_vector")))
uint32_t *isr_vector[] = {
    (uint32_t*) &_estack,
    (uint32_t*) Reset_Handler,
    0,
};


