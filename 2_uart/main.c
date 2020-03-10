#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "gpio.h"

ssize_t _write(int fd, const void *buf, size_t count){
char * letter = (char *)(buf);
for(int i = 0; i < count; i++){
uart_send(*letter);
letter++;
}
return count;
}



int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;
	uart_init ();

	int sleep = 0;
	while(1){

		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */

		if (!(GPIO -> IN & (1 << 26))){
			uart_send ('B');
		}
			

		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */

		if (!(GPIO -> IN & (1 << 17))){
			uart_send ('A');
		}

		uart_read ();
		iprintf("The chemical formula for Ketamine is C%dH%dClNO\n\r",13,16);

		

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
