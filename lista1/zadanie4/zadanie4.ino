// Autor: Mikołaj Kowalik
// Indeks: 283476

//zadanie nr 4

// korzystam z arduino IDE
// aktualnie nie mam arduino uno, korzystałem z arduino leonardo
//z tego względu proszę o łagodniejsze traktowanie api, ponieważ na leonardo piny są inaczej podłączone
//i nieestetycznie korzysta się z niskiego poziomu 

//układ na jednym pinie ma podłączoną diodę oraz buzzer (zdjęcie)
#define OUT_PIN 1
#define DEBUG 0

#define LONG_TIME 1000
#define SHORT_TIME 200
#define L_PAUSE 100
#define PAUSE 1000

// International Morse Code Table:
// http://www.nicholson.com/rhn/morsecodetable.html




char * morseTab[256];        


//lista1\zadanie4\zadanie4.ino:17:38: sorry, unimplemented: non-trivial designated initializers not supported 
//char table[][10] = { [250] = "Abcde" };
//jako, że kompilator nie wspiera tej eleganckiej notacji zdecydowałem się na inicjalizowanie tej tablicy w setup...


void setup() {
  Serial.begin(9600); 

  pinMode( OUT_PIN, OUTPUT);

  morseTab['A'] = ".-";       
  morseTab['B'] = "-...";    
  morseTab['C'] = "-.-.";   
  morseTab['D'] = "-..";   
  morseTab['E'] = ".";   
  
  morseTab['F'] = "..-.";
  morseTab['G'] = "--.";      
  morseTab['H'] = "....";    
  morseTab['I'] = "..";     
  morseTab['J'] = ".---";  
   
  morseTab['K'] = "-.-";      
  morseTab['L'] = ".-..";    
  morseTab['M'] = "--";     
  morseTab['N'] = "-.";    
  morseTab['O'] = "---";  
  
  morseTab['P'] = ".--.";     
  morseTab['Q'] = "--.-";    
  morseTab['R'] = ".-.";    
  morseTab['S'] = "...";   
  morseTab['T'] = "-";    
  
  morseTab['U'] = "..-";    
  morseTab['V'] = "...-";   
  morseTab['W'] = ".--";    
  morseTab['X'] = "-..-";   
  morseTab['Y'] = "-.--";   
  morseTab['Z'] = "--..";   
  
  morseTab['0'] = "-----";  
  morseTab['1'] = ".----";  
  morseTab['2'] = "..---";  
  morseTab['3'] = "...--";  
  morseTab['4'] = "....-";  
  
  morseTab['5'] = ".....";  
  morseTab['6'] = "-....";  
  morseTab['7'] = "--...";  
  morseTab['8'] = "---..";  
  morseTab['9'] = "----.";  
  
  morseTab['.'] = ".-.-.-";
  morseTab[','] = "--..--";
  morseTab['?'] = "..--..";

  morseTab[' '] = "";
  

}

void loop() {

        //jeśli są jakieś dane
        if (Serial.available() > 0) {
                //odczytaj znak
                int znak = Serial.read();

                //zamiana liter na duze (odległość dużych liter od małych wynosi 32 (trzeba zgasić jeden bit)
                znak = ( znak >= 97 && znak <= 122 )? znak&(~(1<<5)): znak;

                //jeśli chcemy by urządzenie wypisywało nam co wyświetla/odtwarza, na górze można zmienić DEBUG na 1
                if( DEBUG )
                  Serial.println( morseTab[ znak ] );
                                
                for(int i=0; i < strlen( morseTab[ znak ]); ++i){
                  digitalWrite(OUT_PIN, HIGH);
                  delay( (morseTab[ znak ][i] == '-') ? LONG_TIME : SHORT_TIME );
                  digitalWrite(OUT_PIN, LOW);
                  delay( L_PAUSE );
                }
        }

        delay( PAUSE );

}
