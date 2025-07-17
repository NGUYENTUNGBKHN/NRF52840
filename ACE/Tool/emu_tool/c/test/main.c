
#define UART0_DR (*(volatile unsigned int *)0x40000000)


#define UART0_FR (*(volatile unsigned int *)0x40000004)
#define UART_FR_TXFF (1 << 5) // Transmit FIFO Full bit

void send_char(char c) {
    while (UART0_FR & UART_FR_TXFF);
    UART0_DR = (unsigned int)c;
}

void print_string(const char *s) {
    while (*s != '\0') {
        send_char(*s);
        s++;
    }
}

int main() {
    print_string("Hello from Cortex-M4 Emulator!\n");
    while (1) {
    }

    return 0;
}