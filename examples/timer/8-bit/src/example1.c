#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
int extraTime = 0;

int main(void){

    DDRC = (1 << DDC5);

    TCCR0A = (1 << WGM01); //Set CTC Bit

    OCR0A = 195;
    TIMSK0 = (1 << OCIE0A);

    sei();

    TCCR0B = (1 << CS02) | (1 << CS00); //start at 1024 prescalar

    while(1) {
    	// Do nothing
    }
}

ISR(TIMER0_COMPA_vect) {
    extraTime++;

    if(extraTime > 100)
    {
        extraTime = 0;
        PORTC ^= (1 << PORTC5);
    }
}
