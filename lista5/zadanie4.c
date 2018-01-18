#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define TRUE 1


void init_master();
void init_slave();  
void send_byte( int8_t liczba );
void timer_tick();

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

FILE uart_file;

ISR(SPI_STC_vect)            //Kod wykonywany po zgłoszeniu przerywania SPI_STC
{
    int8_t bajt = SPDR;        //Pobieramy wartość wysłaną przez Master
    printf("odebrano: %d\n\r", bajt );
}



int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  
  init_master();
  init_slave();  
  
  sei();
  printf("world!\n\r");
  
  int8_t liczba = 0;
  while( TRUE ) {
  	send_byte( liczba );
  	liczba++;
  }
}


void init_master(){
	DDRD = _BV(3) | _BV(5);
	
}


void init_slave(){
	
	DDRB = _BV(4);
	//przerwania i interfejs SPI 
    SPCR = ( 1 << SPIE ) | ( 1 << SPE );    
}



void send_byte( int8_t liczba ){
	for( int i=0; i<8; ++i ){
		if( liczba & _BV(7-i) )
			PORTD |= 1<<3;
		else
			PORTD &= ~(1<<3);
		_delay_ms(10);
		timer_tick();
	}
}


void timer_tick(){
	PORTD |= _BV(5);
	_delay_ms(10);
	PORTD &= ~( _BV(5) );
}

