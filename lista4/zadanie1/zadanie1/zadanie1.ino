#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem


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

static int16_t time_reset = 0;

ISR(TIMER1_OVF_vect)
{ 
  time_reset++;
  PORTD |= 4; //zapalenie diody na pinie 2
  printf("Time: %d\n", time_reset); //ta instrukcja sama wygeneruje delay ;)
  TCNT1 = 3277; // preload timer 50ms - mniej wiecej tyle trwa wykonanie printf
  PORTD = PORTD&(~4);     //zgaszenie diody na pinie 2 
}



int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  DDRD |= 4; // ustawienie pinu 2 na wyjscie

  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TCNT1 = 0;                // preload timer 65536-16MHz/256/1Hz
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  
  sei();        //wlaczenie przerwan
  while(1) {
   
  }
}

