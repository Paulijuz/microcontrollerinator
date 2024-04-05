#include <stdint.h>

#define GPIO0 ((NRF_GPIO_REGS0*)0x50000000)


typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t RESERVED1[118];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS0;


void led_init(){
	  GPIO0->PIN_CNF[17] = 1;
};

void led_off(){
	GPIO0->OUTSET |= (1<<17);
};

void led_on(){
	GPIO0->OUTCLR |= (1<<17);
};


int main(){

	led_init();
	int sleep = 0;
	while(1){
		led_on();
		sleep = 1000000;
		while(--sleep);
		led_off();
		sleep = 1000000;
		while(--sleep);
	}
	return 0;
}
