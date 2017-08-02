#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#define FOSC F_CPU
#define BAUD 4800
#define MYUBRR FOSC/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Check Cheat sheet for details about instruction
void USART_Init(unsigned int ubrr) {
   UBRR0H = (unsigned char)(ubrr>>8);
   UBRR0L = (unsigned char)ubrr;
   UCSR0B = (1<<RXEN0)|(1<<TXEN0);
   UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( unsigned char data ){
   while ( !( UCSR0A & (1<<UDRE0)) );
   UDR0 = data;
}

unsigned char USART_Receive( void ){
   while ( !(UCSR0A & (1<<RXC0)) );
   return UDR0;
}

void USART_TX_int() {
	UCSR0B |= (1 << TXCIE0);
	sei();
}

ISR(USART_TX_vect) {
	PORTC ^= (1 << PC5);
}

int main(void) {

	USART_Init(MYUBRR);
	USART_TX_int();

	DDRC = (1 << DDC5);

	while(1) {
		USART_Transmit('a');
		_delay_ms(1000);
	}
	return 0;
}
