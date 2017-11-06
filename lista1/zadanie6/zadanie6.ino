// Autor: Mikołaj Kowalik
// Indeks: 283476

//zadanie nr 6 (dodatkowe)

// korzystam z arduino IDE
// kod przepisane z leonardo, część korzysta z api - nie było już sensu tego zmieniać (arduino leonardo inaczej obsługuje porty)
// piny na leonardo nie są podłączane 0-7 do portu D itd. dlatego wcześniej używałem api, bo uznałem korzystanie z niskiego poziomu za nieestetyczne w tym wypadku
// tak samo dla odczytu stanu pinu nie korzystałem już z PINB


//czas drgania od producenta: 
#define DRGANIE 20 /* ms */

#define BUTTON_NEXT  10
#define BUTTON_PREV  11
#define BUTTON_RESET 12

#define R_DISPLAY 8
#define L_DISPLAY 9


//nie używam wbudowanej funkcji z api do obsługi wyświetlaczy 7-segmentowych
/*
  A_PIN 1
  B_PIN 2
  C_PIN 3
  D_PIN 4
  E_PIN 5
  F_PIN 6
  G_PIN 7
*/

int stan = 0;

inline void obsluzPrzycisk( int przycisk ){
    //przeczekanie drgania po wcisnieciu przycisku
    delay( DRGANIE );
    
    switch( przycisk ){
      case BUTTON_NEXT:
          ++stan;
          stan = ( stan > 99 )? 0 : stan;
        break;

      case BUTTON_PREV:
          --stan;
          stan = ( stan < 0 )? 99 : stan; 
        break;

      case BUTTON_RESET:

          stan = 0;
        break;
    }
    
    //przeczekanie stanu wysokiego
    while( digitalRead( przycisk ) == HIGH );
    //przeczekanie drgania po puszczeniu przycisku
    delay( DRGANIE );
}

void wyswietlCyfre( int cyfra ){
  //tablica przechowywująca które piny mają być w stanie wysokim, a które w niskim dla poszczególnych cyfr
  static int digits[] = { 0x7E, 0x0C, 0xB6, 0x9E, 0xCC, 0xDA, 0xFA, 0x0E, 0xFE, 0xDE};
 
  PORTD = digits[ cyfra ];
  delayMicroseconds(5000); //poprzednie diody muszą jeszcze zgasnąć 
}


void wyswietl( int liczba ){
  int jednosci = liczba % 10;
  int dziesiatki = (liczba/10)%10;

  //wyswietlanie cyfry jednosci
  digitalWrite( R_DISPLAY, HIGH );
  wyswietlCyfre( jednosci ); 
  digitalWrite( R_DISPLAY, LOW );
  
  //wyswietlanie cyfry dziesiatek
  digitalWrite( L_DISPLAY, HIGH );
  wyswietlCyfre( dziesiatki );
  digitalWrite( L_DISPLAY, LOW );
}


void setup() {
  
  pinMode( BUTTON_NEXT,  INPUT );
  pinMode( BUTTON_PREV,  INPUT );
  pinMode( BUTTON_RESET, INPUT );
  pinMode( L_DISPLAY, OUTPUT);
  pinMode( R_DISPLAY, OUTPUT);

  //ustawienie potrzebnych pinów na output /* uno */
  DDRD = 0xFE;
}

void loop() {


  
  if( digitalRead(BUTTON_RESET) == HIGH )
    obsluzPrzycisk( BUTTON_RESET );
  
  if( digitalRead(BUTTON_PREV) == HIGH )
    obsluzPrzycisk( BUTTON_PREV );
  
  if( digitalRead(BUTTON_NEXT) == HIGH )
    obsluzPrzycisk( BUTTON_NEXT );

 
  wyswietl( stan );  
}
