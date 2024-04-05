#include "uart.h"

void button_init(){ 
	for (int i = 13; i <= 16; i++) {
		GPIO->PIN_CNF[i] = (3 << 2);
	}
}

int main(){
    uart_init();

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
        // while(--sleep); // Delay

		/* Check if button 1 is pressed;
		 * turn on LED matrix if it is. */
		if (!(GPIO->IN & (1 << 13))) {
			for(int i = 17; i <= 20; i++){
				GPIO->OUT &= ~(1 << i);
			}
            uart_send('A');
		}

		/* Check if button 2 is pressed;
		 * turn off LED matrix if it is. */
		if (!(GPIO->IN & (1 << 14))) {
			for(int i = 17; i <= 20; i++){
				GPIO->OUT |= (1 << i);
			}
            uart_send('B');
		}

		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}
