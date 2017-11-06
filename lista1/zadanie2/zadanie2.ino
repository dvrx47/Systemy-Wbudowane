// Autor: Mikołaj Kowalik
// Indeks: 283476

//zadanie nr 2

// korzystam z arduino IDE
// aktualnie nie mam arduino uno, korzystałem z arduino leonardo
//z tego względu proszę o łagodniejsze traktowanie api, ponieważ na leonardo piny są inaczej podłączone
//i nieestetycznie korzysta się z niskiego poziomu 

//do zadania zalaczam zdjecie ukladu.

//pin nasłuchujący
#define IN_PIN 1
//pin z napięciem do diody
#define LED_PIN 2



void setup() {
  pinMode( LED_PIN, OUTPUT );
  pinMode( IN_PIN, INPUT );
}


void loop() {
    static unsigned long timeStart = 0;
    static unsigned long timeEnd = 0;
    static int pomiarBool = 0;
    if( digitalRead(IN_PIN) == HIGH){
      
      if ( !pomiarBool ){
        pomiarBool++; //oznaczenie, że uruchomiono pomiar czasu
        timeStart = millis(); //pobranie czasu startu pomiaru
      }
      
    }
    else
      {
        if(pomiarBool){
          pomiarBool = 0;
          
          timeEnd = millis(); //pobranie czasu zakonczenia pomiaru
          unsigned long diff = timeEnd-timeStart; 
          delay(1000); //odczekanie sekundy po pomiarze

          //zapalenie i zgaszenie lampki
          digitalWrite( LED_PIN, HIGH ); 
          delay( diff );
          digitalWrite( LED_PIN, LOW );
        }
      }
      
}
