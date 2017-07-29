#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void) {

	// Set Data Direction for PD6 to output for the LED
	DDRD |= (1 << PD6);

	// Clear OC0A on Compare Match, set OC0A at BOTTOM
	TCCR0A = (1 << COM0A1)
			// Fast PWM
			| (1 << WGM01) | (1 << WGM00);

	// No clock prescaler clk/1
	TCCR0B = (1 << CS00);

	while (1) {

		// Increasing the LED brightness
		OCR0A +=1;
		_delay_ms(100);

		// If the 8-bit register OCR0A overflows, reset it
		if(OCR0A > 255) {
			OCR0A = 0;
		}
	}

	return(0);					// should never get here, this is to prevent a compiler warning
}


