/*
 * atmega32u4.c
 *
 * Created: 30-06-2019 21:04:58
 * Author : Aniket Mazumder
 */ 
#define F_CPU 16000000UL
#define _BV(pinnumber) 1<<pinnumber
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB|=_BV(PB6);
    /* Replace with your application code */
    while (1) 
    {
		PORTB|=_BV(PB6);
		_delay_ms(1000);
		PORTB&=~_BV(PB6);
		_delay_ms(500);
    }
}

