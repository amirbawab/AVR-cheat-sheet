//#include <avr/io.h>
//#include <avr/interrupt.h>
//
//#ifndef F_CPU
//#define F_CPU 1000000UL
//#endif
//
//int main(void) {
//
//	// Set DDD2 to input
//    DDRD &= ~(1 << DDD2);
//
//    // Set PORTD2 to pull-up resistor
//    PORTD |= (1 << PORTD2);
//
//    // Set External Interrupt Control Register A
//    // to 00: The low level of INT1 generates an interrupt request.
//    EICRA |= (1 << ISC00);
//
//    // Set External Interrupt Mask Register
//    // to INT0 to activate interrupt INT0
//    EIMSK |= (1 << INT0);
//
//    // Set DDC5 to output
//    DDRC |= (1 << DDC5);
//
//    // Enable interrupts
//    sei();
//
//    // Loop forever
//    while(1){
//    	// Do nothing
//    }
//    return 0;
//}
//
//// Handle interrupt at INT0
//ISR (INT0_vect) {
//
//	// Toggle LED
//    PORTC ^= (1 << PORTC5);
//}
