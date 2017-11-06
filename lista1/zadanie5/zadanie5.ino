// Autor: Mikołaj Kowalik
// Indeks: 283476

//zadanie nr 5

// korzystam z arduino IDE
// aktualnie nie mam arduino uno, korzystałem z arduino leonardo
//z tego względu proszę o łagodniejsze traktowanie api, ponieważ na leonardo piny są inaczej podłączone
//i nieestetycznie korzysta się z niskiego poziomu 

//do wyznaczania kolejnych kodów gray'a skorzystałem z algorytmu:
//http://eduinf.waw.pl/inf/alg/006_bin/0025.php

//nie korzystałem z INPUT_PULLUP - do przycisków używałem rezystorów 10 kOhm

//czas drgania od producenta: 
#define DRGANIE 20 /* ms */

#define BUTTON_NEXT  1
#define BUTTON_PREV  2
#define BUTTON_RESET 3

#define LED_ZERO  4
#define LED_TWO   5
#define LED_THREE 6
#define LED_FOUR  7


inline void aktualizujDiody( int stan ){
  digitalWrite( LED_ZERO,  (stan)&1    );
  digitalWrite( LED_TWO,   (stan>>1)&1 );  
  digitalWrite( LED_THREE, (stan>>2)&1 );  
  digitalWrite( LED_FOUR,  (stan>>3)&1 );     
}

inline void obsluzPrzycisk( int przycisk ){
    static int stan = 0;
    //przeczekanie drgania po wcisnieciu przycisku
    delay( DRGANIE );
    
    switch( przycisk ){
      case BUTTON_NEXT:
          ++stan;
          stan = ( stan > 15 )? 0 : stan;
        break;

      case BUTTON_PREV:
          --stan;
          stan = ( stan < 0 )? 15 : stan; 
        break;

      case BUTTON_RESET:
          stan = 0;
        break;
    }
    
    //przeczekanie stanu wysokiego
    while( digitalRead( przycisk ) == HIGH );
    //przeczekanie drgania po puszczeniu przycisku
    delay( DRGANIE );

                     //przeliczanie na kod gray'a
    aktualizujDiody( stan ^ (stan>>1) );
}

void setup() {
  pinMode( BUTTON_NEXT,  INPUT );
  pinMode( BUTTON_PREV,  INPUT );
  pinMode( BUTTON_RESET, INPUT );

  pinMode( LED_ZERO,  OUTPUT );
  pinMode( LED_TWO,   OUTPUT );
  pinMode( LED_THREE, OUTPUT );
  pinMode( LED_FOUR,  OUTPUT );
}

void loop() {
  
  if( digitalRead(BUTTON_RESET) == HIGH )
    obsluzPrzycisk( BUTTON_RESET );
  
  if( digitalRead(BUTTON_PREV) == HIGH )
    obsluzPrzycisk( BUTTON_PREV );
  
  if( digitalRead(BUTTON_NEXT) == HIGH )
    obsluzPrzycisk( BUTTON_NEXT );
  
}
