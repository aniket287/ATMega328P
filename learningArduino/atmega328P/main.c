
// Simple program to blink an LED at a desired time instant
// Program to learn setting and clearing of specific bits in atmega328P
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>


int main(void)
{
	
	// clear DDRB
	DDRB=0;
	// set PORTB5 to output
	DDRB|=0B00100000;

   
    while (1) 
    {
		PORTB|=0B00100000;// SET bit 5. LED switches on
		//_delay_ms(100);
		PORTB&=0b11011111; // CLEAR bit 5. LED switches off
		//_delay_ms(100);
    }
}

