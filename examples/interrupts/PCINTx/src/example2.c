#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

int intFlag = 0;

int main(void) {

	// Set DDB1 to input
    DDRB &= ~(1 << DDB1);

    // Set PORTB1 to pull-up resistor
    PORTB |= (1 << PORTB1);

    // Set the Pin Change Interrupt Control Register
    // to "PCIE0" (range of PCINTx sharing the interrupt vector with PCINT0)
    PCICR = (1 << PCIE0);

    // Mask out (disable) all PCINTx sharing the same interrupt vector with PCINT1,
    // except for PCINT1 (enable it)
    PCMSK0 = (1 << PCINT1);

    // Set DDC5 to output
    DDRC |= (1 << DDC5);

    // Loop forever
    while(1){
    	if(intFlag == 0) {
			// Enable interrupts
			sei();
    	} else {

    		// Disable interrupts
    		cli();

    		// Debouncing by delaying for 1000ms
    		_delay_ms(1000);

    		// Reset flag to re-enable interrupts
    		intFlag = 0;
    	}
    }
    return 0;
}

// Handle the shared interrupt vector (group 0)
ISR (PCINT0_vect) {

	// Toggle LED
    PORTC ^= (1 << PORTC5);

	// Raise flag to disable interrupts
	intFlag = 1;
}
