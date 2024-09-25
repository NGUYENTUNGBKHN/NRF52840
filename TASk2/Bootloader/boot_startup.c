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
    main();
}



__attribute((section(".isr_vector")))
uint32_t *isr_vector[] = {
    (uint32_t*) &_estack,
    (uint32_t*) Reset_Handler,
    0,
};

