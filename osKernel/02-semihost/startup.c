
#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sidata;
extern void main(void);


void Reset_Handler()
{
    uint32_t *start_data;
    uint32_t *end_data;
    uint32_t *data;


    start_data = &_sdata;
    end_data = &_edata;
    data = &_sidata;
    while (start_data < end_data)
    {
        /* code */
        *start_data++ = *data++;
    }
    

    main();
}


__attribute((section(".isr_vector")))
uint32_t *_isr_vector[] = {
    (uint32_t*) &_estack,
    (uint32_t*) Reset_Handler,
    0
};


