#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define TRUE 1

#define LED_DDR DDRB

#define RED     9	-8
#define GREEN   10	-8
#define BLUE    11	-8

#define DLY 10


#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  #undef ENDIAN
#else
  #define ENDIAN 
#endif


typedef union{
  
  #ifdef ENDIAN
    struct{
      int8_t offset;
      int8_t red;
      int8_t green;
      int8_t blue;
    };
  #else
    struct{
      int8_t blue;
      int8_t green;
      int8_t red;
      int8_t offset;
    };
  #endif
  
  int32_t rgbColor; //0x00RRGGBB;
  
} ColorRGB;

ColorRGB * hsvToRgb( int h, int s, int v )
{
  ColorRGB * res = (ColorRGB*)malloc( sizeof(*res) );
  int i;
  int f, p, q, t;
  if( s == 0 ) {
    res->red = res->green = res->blue = 255*v/100;
    return res;
  }
    
  h = h*100/60;  
  i = h - h%100;
  f = h - i;
  p = v * ( 100 - s )/100;
  q = v * ( 100 - s*f/100)/100;
  t = v * ( 100 - s * ( 100 - f )/100 )/100;
  i /= 100;

  switch( i ) {
    case 0:
      res->red = 255*v/100;
      res->green = 255*t/100;
      res->blue = 255*p/100;
      break;
    case 1:
      res->red = 255*q/100;
      res->green = 255*v/100;
      res->blue = 255*p/100;
      break;
    case 2:
      res->red = 255*p/100;
      res->green = 255*v/100;
      res->blue = 255*t/100;
      break;
    case 3:
      res->red = 255*p/100;
      res->green = 255*q/100;
      res->blue = 255*v/100;
      break;
    case 4:
      res->red = 255*t/100;
      res->green = 255*p/100;
      res->blue = 255*v/100;
      break;
    case 5:
      res->red = 255*v/100;
      res->green = 255*p/100;
      res->blue = 255*q/100;
      break;
  }

  return res;
}


void setRgbColor( ColorRGB * kolor, int free_bool ){
	OCR1A = 255 - kolor->red;	//red
	OCR1B = 255 - kolor->green; //green
	OCR2A = 255 - kolor->blue;  //blue
	if( free_bool )
		free(kolor);
}



void init_pins(){
	LED_DDR = _BV(RED) | _BV(GREEN) | _BV(BLUE) ;
 
	TCCR1A |= (1 << WGM10);
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS11);
	
	TCCR1A |= (1 << COM1A1);
	TCCR1A |= (1 << COM1B1);

	TCCR2A |= (1 << WGM20);
	TCCR2A |= (1 << WGM21);
	TCCR2B |= (1 << CS21);
	TCCR2A |= (1 << COM2A1);
}


//funkcje dobrane na potrzeby zadania - posłużyłem się funkcjami przybliżonymi
int exp_int( int x ){ 
	return x*x/157;
}

void zgas(int h){
	for(int i = 157; i >= 0; --i){
		setRgbColor( hsvToRgb( h, 100, sin_int(exp_int(i))) , 1 ) ;	
		_delay_ms(DLY);
	}
}

void zapal(int h){
	for(int i = 1; i <= 157; ++i){
		setRgbColor( hsvToRgb( h, 100, sin_int(exp_int(i))), 1 );	
		_delay_ms(DLY);
	}
}

int sin_int( int x ){ //x \in [0, 314]  y \in [0, 100] 
	return -((x-157)*(x-157))/246+100;
}

int main(){
	
	init_pins();

	int h = 120;
	setRgbColor( hsvToRgb( h, 100, 100), 1 );

	while( TRUE ){		
		zgas(h);
		h = random()%360;
		zapal(h);
	}
}
