
// Simple program to blink an LED at a desired time instant
// Program to learn setting and clearing of specific bits in arduino
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>


int main(void)
{
	
	// set PORTB5 to output
	DDRB|=0B00100000;
	
	uint8_t i=1;
	while (1)
	{
		i++;
		PORTB|=0B00100000;// SET bit 5. LED switches on
		_delay_ms(1000);
		PORTB&=0b11011111; // CLEAR bit 5. LED switches off
		_delay_ms(5000);
	}
}

