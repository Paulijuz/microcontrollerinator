#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)

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
} NRF_GPIO_REGS;

void button_init(){ 
	for (int i = 13; i <= 16; i++) {
		GPIO->PIN_CNF[i] = (3 << 2);
	}
}

int main(){
	// Configure LED Matrix
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET |= (1 << i);
		// GPIO->OUTCLR |= (1 << i);
		GPIO->OUT |= (1 << i);
	}

	// Configure buttons -> see button_init()
	button_init();
	
	int sleep = 0;
	while(1){

		/* Check if button 1 is pressed;
		 * turn on LED matrix if it is. */
		if (!(GPIO->IN & (1 << 13))) {
			for(int i = 17; i <= 20; i++){
				GPIO->OUT &= ~(1 << i);
			}
		}

		/* Check if button 2 is pressed;
		 * turn off LED matrix if it is. */
		if (!(GPIO->IN & (1 << 14))) {
			for(int i = 17; i <= 20; i++){
				GPIO->OUT |= (1 << i);
			}
		}

		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}
