
// Code to alternately flip bits every cycle

#define F_CPU	16000000UL
#include <util/delay.h>
#include <avr/io.h>


int main(void)
{
	DDRB=0;// Clear DDRB 
    DDRB=0b00100000; // SET PB5 to OUTPUT
	
    
	while (1) 
    {
		//change state of PORTB5(SET/CLEAR alternately)
		PORTB^=0b00100000; // PORTB= PORTB^0b00100000
		//_delay_us(1000000);
    }
}

