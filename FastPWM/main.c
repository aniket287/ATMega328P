/*
Finished

Code to setup fast PWM using timer1 of atmega328P
 */

#define F_CPU 16000000UL
#define _BV(X) (1<<X)
#define TOPValue 1600 // The Top value for the PWM, this along with the prescaler decides the frequency of the PWM
//when prescaler is 1(one tick takes 1/16e6 s), then choosing a value of 1600 gives a total time of 1600/16e6 s or a frequency of 10KHz.
#include <avr/io.h>
#include <util/delay.h>



void setupPWMTimer();// Function to setup PWM using timer1

uint8_t dutyCycle=70; //dutyCycle in percentage. This variable should be varied over the course of the gait cycle
uint16_t COMPValue=0; //value to be set to the compare register corresponding to a duty cycle


int main()
{
	
	//Setting the OC1A as output
	DDRB|=_BV(PB1);
	
	setupPWMTimer();// Setup PWM
	
	
	while(1)
	{
		
		if(dutyCycle<100)
		++dutyCycle;
		if(dutyCycle==100)
		dutyCycle=0;
		
		_delay_ms(100);
		
		COMPValue=(dutyCycle*0.01)*TOPValue;
		OCR1A=COMPValue;
		
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


