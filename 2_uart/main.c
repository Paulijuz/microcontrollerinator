#include <stdio.h>
#include <sys/types.h>
#include "uart.h"

ssize_t _write(int fd, const void *buf, size_t count) {
	char * letter = (char *)(buf);
	
	for(int i = 0; i < count; i++){
		uart_send(*letter);
		letter++;
	}

	return count;
}

void button_init(){ 
	for (int i = 13; i <= 16; i++) {
		GPIO->PIN_CNF[i] = (3 << 2);
	}
}

int led_state = 0;

void leds_on() {
	led_state = 1;
	for(int i = 17; i <= 20; i++){
		GPIO->OUT &= ~(1 << i);
	}
}

void leds_off() {
	led_state = 0;
	for(int i = 17; i <= 20; i++){
		GPIO->OUT |= (1 << i);
	}
}

int main(){
    uart_init();

	int sleep = 1000000;

	for (int i = 0; i < 1; i++) {
		iprintf("Gjennomsnitts karakteren i TTK4235 var B %d\r\n", i);
	}

	// Configure LED Matrix
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET |= (1 << i);
		// GPIO->OUTCLR |= (1 << i);
		GPIO->OUT |= (1 << i);
	}

	// Configure buttons -> see button_init()
	button_init();
	
	while(1){
        // while(--sleep); // Delay

		/* Check if button 1 is pressed;
		 * turn on LED matrix if it is. */
		if (!(GPIO->IN & (1 << 13))) {
			leds_on();
            uart_send('A');
		}

		/* Check if button 2 is pressed;
		 * turn off LED matrix if it is. */
		if (!(GPIO->IN & (1 << 14))) {
			leds_off();
            uart_send('B');
		}

		char x;
		if((x = uart_read())) {
			led_state = !led_state;

			if(led_state) leds_on();
			else leds_off();

			uart_send(x);
		}

		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}
