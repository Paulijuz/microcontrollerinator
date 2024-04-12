#include "gpiote.h"
#include "ppi.h"
#include "gpio.h"

void init_buttons() {
    for (int i = 0; i < 4; i ++) {
        GPIOTE->CONFIG[i] = (1 << 0) | ((13 + i) << 8) | (1 << 16);
        GPIO->PIN_CNF[13 + i] = 3 << 2;
    }
}

void init_leds() {
    for (int i = 0; i < 4; i ++) {
        GPIOTE->CONFIG[i + 4] = (3 << 0) | ((17 + i) << 8) | (3 << 16) | (0 << 20);
    }   
}

void init_ppi() {
    for (int i = 0; i < 4; i++) {
        PPI->PPI_CH[i].EEP = (uint32_t)&GPIOTE->IN[i];
        PPI->PPI_CH[i].TEP = (uint32_t)&GPIOTE->OUT[i+4];
    }
    PPI->CHENSET = 0b1111;
}

int main() {
    init_buttons();
    init_leds();
    init_ppi();

    while (1) {};

    return 0;
}