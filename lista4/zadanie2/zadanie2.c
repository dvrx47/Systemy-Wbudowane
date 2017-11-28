#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>



#define PODZIAL 100
#define TIMER_INIT 64911

int pos = 0;
int8_t buffer[PODZIAL];

ISR(TIMER1_OVF_vect)
{ 
	TCNT1 	= TIMER_INIT;
	if( buffer[pos] ){
		PORTD |= (1<<4);
	}else{
		PORTD &= ~(1<<4);
	}
	buffer[pos] = PIND & (1<<2);
	pos = (pos+1)%PODZIAL;
	
}


int main()
{
	DDRD |= 1<<4; //ustawienie pinu 3 na output, 2 na input
	DDRD &= ~(1<<2);

	
	TCCR1A 	= 	0;
	TCCR1B 	= 	0;
	TCCR1B 	|= 	(1 << CS12);    // 256 prescaler 
	TCNT1 	= 	TIMER_INIT;                // preload timer 65536-16MHz/256/100Hz (625)
	TIMSK1 	|= 	(1 << TOIE1); // enable timer overflow interrupt

	
	sei(); //wlaczenie przerwan
	while(1) {

	}
}


