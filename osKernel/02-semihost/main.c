#include <stdint.h>
#include "reg.h"

#define RX_PIN_NUMBER 8
#define TX_PIN_NUMBER 6
#define CTS_PIN_NUMBER 7
#define RTS_PIN_NUMBER 5
#define PORT0 0

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

static int semihost_call(int service, void *opaque)
{
    register int r0 asm("r0") = service;
    register void *r1 asm("r1") = opaque;
    register int result asm("r0");
    asm volatile("bkpt 0xab"
                : "=r" (result) : "r" (r0), "r" (r1));
    return result;
}

enum SEMISHOT_SVC {
    SYS_WRITE = 0x05,
};


int main()
{
    char message[] = "Hello World!\n";
    uint32_t param[] = { 1, (uint32_t) message, sizeof(message) };
    logInit();

    logPrintf("SemiHost \n");

	semihost_call(SYS_WRITE, (void *) param);
    while (1)
    {
        /* code */
    }
    
    return 0;
}
