#include <stdint.h>
#include "reg.h"

#define RX_PIN_NUMBER 8
#define TX_PIN_NUMBER 6
#define CTS_PIN_NUMBER 7
#define RTS_PIN_NUMBER 5
#define PORT0 0

uint32_t *activates(uint32_t *stack);
void syscall(void);

int logPrintf(const char *str)
{
    while(*str)
    {
        uart0->TXD = *str++;
		while(uart0->EVENTS_TXDRDY != 0x01)
        {

        }
		uart0->EVENTS_TXDRDY = 0x00;
    }
    return 0;
}

void logInit()
{
    uart0->BAUDRATE = UART_BAUDRATE_115200;     /* 115200 baud */
    uart0->CONFIG = UART_CONFIG_HWFC_DIS |      /* hard flow off */
                    UART_CONFIG_PARITY_EXE |    /* parity exc */
                    UART_CONFIG_STOP_ONE;       /* stop bit one */
    uart0->ENABLE = UART_ENABLE_REGISTER_EN;    /* Enable uart  */        
    uart0->PSEL_TXD = UART_TXD_CONNECT |        
                    (PORT0 << UART_TXD_PORT_POS) | 
                    (TX_PIN_NUMBER << UART_TXD_PIN_POS);
    uart0->PSEL_RXD = UART_RXD_CONNECT |        
                    (PORT0 << UART_RXD_PORT_POS) | 
                    (RX_PIN_NUMBER << UART_RXD_PIN_POS);

    /* Interrupt */
    uart0->INTENSET = UART_INTENSET_TXDRDY_EN;
    uart0->TASKS_STARTTX = 0x01;
}


void task1(void)
{
    logPrintf("usertask : 1st call of userstask! \n");
    logPrintf("usertask : Now, return to kernel mode \n");
    syscall();
    logPrintf("usertask : 2nd call of userstask! \n");
    logPrintf("usertask : Now, return to kernel mode \n");
    syscall();
    while (1)
    {
    }
}

int main()
{
    uint32_t usertask_stack[256];
    uint32_t *usertask_stack_start = usertask_stack + 256 - 16;
    usertask_stack_start[8] = (uint32_t) &task1;

    logInit();
    logPrintf("OS : Context Switch\n");
    logPrintf("OS : Calling the usertask (1st time)\n");
    usertask_stack_start = activates(usertask_stack_start);
    logPrintf("OS : Return to the OS mode\n");
    logPrintf("OS : Calling the usertask (2nd time)\n");
    usertask_stack_start = activates(usertask_stack_start);
    logPrintf("OS : Return the OS mode \n");
    logPrintf("OS : Going to infinite loop ... \n");
    
    while (1)
    {
    }
}
