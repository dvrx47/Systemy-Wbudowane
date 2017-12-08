#include <avr/io.h>


#define LED_DDR 			DDRB
#define RED     			9  -8
#define MAX_VALUE 			90000.0
#define SAMPLES_TO_AVG 		1
#define TRUE 				1


void init_led_pin(){
	LED_DDR = _BV(RED);
}

void init_timer(){

	TCCR1A |= (1 << WGM10);
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS11);

	TCCR1A |= (1 << COM1A1);
	TCCR1A |= (1 << COM1B1);
}


void init_A0(){
  ADMUX = _BV(REFS0);
  DIDR0 = _BV(ADC0D);
  
  ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2) | _BV(ADEN) ;
}


void init(){
  init_led_pin();
  init_timer();
  init_A0();
  
  OCR1A = 1000; 
}

void setVal( int val ){
  OCR1A = 255 - val;
}


int read_A0(){
	ADCSRA |= _BV(ADSC);
  	while( !(ADCSRA & _BV(ADIF)) );
  	ADCSRA |= _BV(ADIF);
  	
  	return ADC;
}


set_led_value(int sensorValue){
			//avg
			sensorValue = sensorValue/SAMPLES_TO_AVG;

			float voltage = sensorValue * (5.0 / 1023.0);
			float r = (voltage*10000.0)/(5.0-voltage);
			r = r/(MAX_VALUE/255.0);
			
			if(r > 255.0)
			  r = 255.0;

			setVal( (int)r );
}


int main(){

	init();
	
	int sensorValue = 0;
	int samples = 0;
	
	while(TRUE){  
  		sensorValue += read_A0(); 
  		samples++;
  		
		if( samples == SAMPLES_TO_AVG ){
			
			set_led_value( sensorValue );
			
			//reset
			samples = 0;
			sensorValue = 0;
		}
	}
	
	
}
