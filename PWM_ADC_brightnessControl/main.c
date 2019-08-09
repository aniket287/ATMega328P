/*
Finished

Main file 
Code to for continuously controlling brightness of an LED using a potentiometer to vary the duty cycle.

Potentiometer - A1, Ground
LED			  - D9, Ground
*/

#define F_CPU 16000000UL
#define _BV(X) (1<<X)
#define TOPValue 1023 // The Top value for the PWM, this along with the prescaler decides the frequency of the PWM
//when prescaler is 1(one tick takes 1/16e6 s), then choosing a value of 1600 gives a total time of 1600/16e6 s or a frequency of 10KHz. 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint16_t dutyCycle=0;

void setupPWMTimer();// Function to setup PWM using timer1 

int main()
{	
	
	//Setting the OC1A as output
	DDRB|=_BV(PB1);
	
	setupPWMTimer();// Setup PWM
	
	
	//Setup ADC
	//enable ADC
	ADCSRA|=_BV(ADEN);
	//pre scale the ADC clock to divide by 128 gives ADC clock frequency of 16e6/128=125KHz
	ADCSRA|=_BV(ADPS2)|_BV(ADPS1)|_BV(ADPS0);
	//select ADC port
	ADMUX|=_BV(MUX0);// port1 selected
	//select ADC voltage reference
	ADMUX|=_BV(REFS0);
	//enable ADC interrupt. 
	ADCSRA|=_BV(ADIE);
	//start initial conversion 
	ADCSRA|=_BV(ADSC);
	
	//enable global interrupts
	sei();
		
	while(1)
	{
				
		//COMPValue=(*0.01)*TOPValue;
		OCR1A=dutyCycle;
		
	}
	
}

/*Function to setup PWM using TIMER1 at max frequency*/
void setupPWMTimer()
{
	//Timer1 and mode 14
	//Setting WGM modes
	TCCR1A|=_BV(WGM11)|_BV(COM1A1);
	TCCR1B|=_BV(WGM12)|_BV(WGM13);
	
	//setting the prescaler to 1 for maximum frequency
	TCCR1B|=_BV(CS10);

	//setting the top value for the PWM counter. This also controls the PWM frequency
	ICR1=TOPValue;
	

}
	
// Interrupt for Conversion completion of ADC	
ISR(ADC_vect)
{
	uint8_t low=ADCL;
	uint8_t high=ADCH;
	dutyCycle=(high<<8)|low;
	
	//start conversion again
	ADCSRA|=_BV(ADSC);
	
}	
