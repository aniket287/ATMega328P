// Code to learn advanced bit shift operations
//X= (1<<5) means that the binary 0b00000001 has been shifted to the left by 5 places essentially representing the binay number 0b00100000; 
#define F_CPU 16000000UL
#define setbit(port,bit) (port|=(1<<bit))// macro to set bit
#define clearbit(port,bit) (port&= ~(1<<bit))// macro to clear bit

#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
int main(void)
{
	int A=1;
	DDRB=0;
	//DDRB|=1<<5;// SET PIN 5 as output
	DDRB|=_BV(5)| _BV(4); // SET pin 5,4 as output
    /* Replace with your application code */
    while (1) 
    {
		A=A+1;
		//PORTB|=(1<<5);// SET bit 5,  
		//setbit(PORTB,5);
		PORTB|=_BV(PORTB5)|_BV(PORTB4);// SET bit 5,4
		//_delay_us(1);
		//PORTB&= (~(1<<5));// CLEAR bit 5
		//clearbit(PORTB,5);
		PORTB&=~(_BV(PORTB5)|_BV(PORTB4));// CLEAR bit 5,4
		//_delay_us(1);
	}
}

