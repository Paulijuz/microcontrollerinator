#include "uart.h"

void uart_init() {
    GPIO->PIN_CNF[6] = 0;
    GPIO->PIN_CNF[8] = 1;

    UART->PSELTXD = 6;
    UART->PSELRXD = 8;


    UART->PSELRTS =~ 0x0;
    UART->PSELCTS =~ 0x0;
    UART->BAUDRATE = 0x00275000;

    UART->ENABLE = 4;
    UART->TASKS_STARTRX = 1; // ?
}

void uart_send(char letter) {
    UART->TASKS_STARTTX = 1;
    
    UART->TXD = letter;
        
    while(!UART->EVENTS_TXDRDY) {}

    UART->EVENTS_TXDRDY = 0;

    UART->TASKS_STOPTX = 1;
}

char uart_read() {
    if (!UART->EVENTS_RXDRDY) return '\0';

    UART->EVENTS_RXDRDY = 0; // why ??

    return UART->RXD;
}