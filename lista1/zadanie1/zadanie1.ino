// Autor: Mikołaj Kowalik
// Indeks: 283476

//zadanie nr 1

// korzystam z arduino IDE
// aktualnie nie mam arduino uno, korzystałem z arduino leonardo
//z tego względu proszę o łagodniejsze traktowanie api, ponieważ na leonardo piny są inaczej podłączone
//i nieestetycznie korzysta się z niskiego poziomu 


/*
 *  W zadaniu wykorzystano 6 diod
 *  podłączone zostały do pinów 1-6
 *  do zadania załączam zdjęcie
 */


 #define LED_FST 1
 #define LED_END 10
 #define STOP 100

void setup() {
  //ustawianie
  for(int i=LED_FST; i<= LED_END ; ++i)
    pinMode(i, OUTPUT);
}

void loop() {

  //zaczynam od pinu pierwszego
  static int ledNr = LED_FST;
  // dir (direction) - zmienna ustalająca kierunek przemieszczania się świecącej diody 
  static int dir = 1;

  //zapalanie i gaszenie diody
  digitalWrite( ledNr, HIGH );
  delay( STOP );
  digitalWrite( ledNr, LOW );

  //wyliczanie następnej diody do zapalenia i zgaszenia
  ledNr += dir;

  //jeśli dioda jest na krawędzi to zmieniamy kierunek
  if( ledNr == LED_END || ledNr == LED_FST )
    dir *= -1;
   
}
