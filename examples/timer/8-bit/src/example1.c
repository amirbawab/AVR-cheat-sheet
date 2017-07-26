#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

// Every 4 times 25ms is equal to 1s
int ms25 = 0;

int main(void){

    // Set pin PC5 as output for the LED
    DDRC = (1 << DDC5);

    // Set timer mode to CTC
    TCCR0A = (1 << WGM01);

    // Calculate the equivalence of 0.25s using
    // an online AVR calculator
    OCR0A = 244;
    TIMSK0 = (1 << OCIE0A);

    // Enable interrupts
    sei();

    // Set prescaler to 1024
    TCCR0B = (1 << CS02) | (1 << CS00);

    while(1) {
    	// Do nothing
    }
}

ISR(TIMER0_COMPA_vect) {

    // Increment 25ms timer
    ms25++;

    // If already 1 second
    if(ms25 > 3) {

        // Reset timer
        ms25 = 0;

        // Toggle LED
        PORTC ^= (1 << PORTC5);
    }
}
