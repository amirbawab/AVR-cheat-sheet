#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRC |= (1 << PC5);
	while (1) {

		// Toggle LED at port PC5
		PORTC ^= (1 << PC5);

		// Delay for 500ms
		_delay_ms(500);
	}
	return 0;
}
