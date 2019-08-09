/* code to learn more about interrupts 
 Timer 1 which is a 16 bit register is used here to learn more about precise control of operations
 The timer is used to generate precise 0.5s interrupts
 Prescaler of 256 for Timer1 has been used giving a Timer compare value of 31250 for an interrupt every 0.5s
 */ 
#define F_CPU 16000000 // define CPU frequency
#define _BV(X) (1<<X)	// Macro for bit shifting operation
#define OCIEA	1	//Output Compare Interrupt A match enable
#define TIMER_COUNTER_INIT 0 // Initializer for timer counter
#define COMP_VAL 31250 //value to be reached by the timer for 0.5s interrupt (requires prescaler of 256)
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

//const uint16_t 
int main()
{
	//set output on PORTB pin5
	DDRB|=_BV(PB5);
	//reset timer1 control registers A B & C
	TCCR1A=TCCR1B=TCCR1C=0;
	//set scaler of 256 for TCCR1B
	TCCR1B|=(_BV(CS12) & ~_BV(CS11) & ~_BV(CS10));
	//set the value for output compare register A. This value is compared with Timer Counter register TCNT1
	OCR1A=COMP_VAL; 
	//enable timer Output Compare A Match interrupt
	TIMSK1|=_BV(OCIEA);  
	//enable global interrupts
	sei();
	//Initialize timer counter to 0;
	TCNT1=TIMER_COUNTER_INIT;
	while(1)
	{
		//loop		
		//_delay_us(2);
	}
	
	
}

ISR(TIMER1_COMPA_vect)
{
	TCNT1=0;
	PORTB^=_BV(PB5);// toggle led pin
}
