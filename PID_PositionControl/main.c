/*
Finished

Code to for continuously controlling a motor Position using P/PI control.
controller output is the value of the dutycycle.

Follower-	A2,Gnd
Reference-	A1,Gnd
LED-		D9,Gnd
Motor Driver:-
	AIN1	-D6
	AIN2	-D7
	A01		-Follower Potentiometer A
	A02		-Follower Potentiometer B
	VM		-Source for Motor
	PWMA	-D9

No velocity control has been implemented in this code. The follower/motor tries to reach the reference position as fast as possible 
*/

#define F_CPU 16000000UL
#define _BV(X) (1<<X)
#define TOPValue 1023 // The Top value for the PWM Timer1, this along with the prescaler decides the frequency of the PWM
//when prescaler is 1, one tick takes 1/16e6 s. Choosing a value of 1600 gives a total time of 1600/16e6 s or a frequency of 10KHz. If 1023 is used then the frequency becomes 16e6/1023 i.e around 15KHz
#define Max 900 //defines max position/angle
#define Min 100 //defines min position/angle
#define LEFT PORTD|=_BV(PD6),PORTD&=~_BV(PD7)// turn motor in left direction 
#define RIGHT PORTD|=_BV(PD7),PORTD&=~_BV(PD6)// turn motor in right direction
#define KP 10
//float KI= 10.0;


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>

//Global Variables
volatile uint16_t ADCoutput=0;// the ADC output ranges from 0 to 1023 and is limited by the resolution of the ADC(10 bit for ATmega328P)
uint16_t controlPot=0; //variable to store the ADC value from main potentiometer
uint16_t followPot=0; //variable to store the ADC value from the control potentiometer

//PID parameters and variables/int16_t KP=10; 
float eint=0.0; 


void setupPWMTimer();// Function to setup PWM using timer1
void setupADC();// Function to setup ADC and read analog data from A1;
uint16_t PID(uint16_t, uint16_t); //Function to do PID control of Motor position

int main()
{
	//Setting the OC1A as output for PWM
	DDRB|=_BV(PB1);
	
	//Setting portD pins 6 and 7 as output for motor direction control
	DDRD|=_BV(PD6)|_BV(PD7);
	
	setupPWMTimer();// Setup PWM
	setupADC();// Setup ADC
	
	
	//enable global interrupts
	sei();
	
	
	while(1)
	{
		
		//OCR1A=ADCoutput; //Assign duty cycle to register OCR1A of timer1 for required duty cycle
		uint16_t dutycycle=PID(controlPot, followPot);
		
		//checking current position of follower
		if(followPot<Min	|| followPot>Max)
		OCR1A=0;
		else
		OCR1A=(uint16_t)dutycycle;
		
		
		//check direction
		if(followPot<controlPot)
		LEFT;
		else
		RIGHT;
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


/*Function to setup ADC in the non free running mode using prescaler of 128, giving a sampling rate of around 9000 samples/s*/
void setupADC()
{
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
}



// Interrupt for Conversion completion of ADC
ISR(ADC_vect)
{
	uint8_t low=ADCL;
	uint8_t high=ADCH;
	ADCoutput=(high<<8)|low;
	
	if(bit_is_set(ADMUX,MUX1)) //if A2 is active
	{
		//select ADC port
		ADMUX&=~_BV(MUX1);// Deactivate A2
		ADMUX|=_BV(MUX0);// Activate A1
		
		controlPot=ADCoutput;
	}
	
	else if(bit_is_set(ADMUX,MUX0))// if A1 is active
	{
		//select second ADC port
		ADMUX&=~_BV(MUX0);// Deactivate A1
		ADMUX|=_BV(MUX1);// Activate A2
		
		followPot=ADCoutput;
	}
	
	
	//start conversion again after ADC value has been obtained
	ADCSRA|=_BV(ADSC);
	
}

//PID control function
uint16_t PID(uint16_t controlPot, uint16_t followPot)
{
	
	int16_t posError=controlPot-followPot;
	int16_t controlSignal=	KP*posError;//Implementation of P only controller
	
	
	//perform check that the control signal remains within the required limit
	if(controlSignal<0)
		controlSignal=controlSignal*-1;
	if(controlSignal>TOPValue)
		controlSignal=TOPValue;
	
	return controlSignal;
	
}
