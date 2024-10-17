#include <stdio.h>
#include "reg.h"

#define RX_PIN_NUMBER 8
#define TX_PIN_NUMBER 6
#define CTS_PIN_NUMBER 7
#define RTS_PIN_NUMBER 5
#define PORT0 0

int tung = 6;

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

int main()
{

    logInit();
    logPrintf("OS : Bootloader 1 \n");

    while (1)
    {
        /* code */
    }
    
    return 0;
}


