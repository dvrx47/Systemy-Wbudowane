#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <util/delay.h>



#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define SERWO_DDR 			DDRB
#define SERWO     			9  -8
#define SAMPLES_TO_AVG 		1
#define TRUE 				1

#define MIN(a,b) ( ((a)<(b))? (a) : (b) )

FILE uart_file;


// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}


// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  // czekaj aż transmiter gotowy
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}


// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}


void init_serwo_pin(){
	SERWO_DDR = _BV(SERWO);
}

void init_timer(){

	TCCR1A |= (1<< WGM11);
	TCCR1B |= (1<< WGM12) | (1<< WGM13) | (1<< CS11);
	ICR1 = 40000;
	TCCR1A |= (1<< COM1A1);

}


void init_A0(){
	ADMUX = _BV(REFS0);
	DIDR0 = _BV(ADC0D);

	ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2) | _BV(ADEN) ;
}

void init_all_uart(){
	// zainicjalizuj UART
	uart_init();
	// skonfiguruj strumienie wejścia/wyjścia
	fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
	stdin = stdout = stderr = &uart_file;
}


void init(){
	init_all_uart();
	init_serwo_pin();
	init_timer();
	init_A0();
}


void setVal( int val ){
  OCR1A = val;
}


int read_A0(){
	ADCSRA |= _BV(ADSC);
  	while( !(ADCSRA & _BV(ADIF)) );
  	ADCSRA |= _BV(ADIF);
  	
  	return ADC;
}


void setServoValue( int value ){
	setVal( value );
}


int main(){

	init();
	printf("Hello\n\r");
	while(TRUE){  
  		int sensorValue = read_A0(); 
  		printf("value = %d\n\r", sensorValue );
  		setServoValue( MIN(1500+4*sensorValue, 4800) );
  		
	}
	
	return 0;
}
