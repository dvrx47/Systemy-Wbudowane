// Autor: Mikołaj Kowalik
// Indeks: 283476

//zadanie nr 3

// korzystam z arduino IDE
// aktualnie nie mam arduino uno, korzystałem z arduino leonardo
//z tego względu proszę o łagodniejsze traktowanie api, ponieważ na leonardo piny są inaczej podłączone
//i nieestetycznie korzysta się z niskiego poziomu 

#define PIN_NUM 10
#define COLUMNS 120

//przy czasie 10ms osiagnelem zadowalajace wizualnie efekty
#define STEP_TIME 10

//tablica kolejno podłączonych pinów 
int PinTab[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

//tablica slowa
char wordTab[ PIN_NUM ][ COLUMNS ] = { 
                         "...#######.........###.....###...........#######.........############.......##############........######.......######...",
                         "..##########.......###.....###..........##########.......############.......##############........#######.....#######...",
                         "####....####.......###.....###........####....####...........###............###...................###..###..####..###...",
                         "###.................###...###.........###....................###............###...................###....#####....###...",
                         ".#####................#####............#####.................###............###########...........###.....###.....###...",
                         "...#######.............###...............#######.............###............###########...........###......#......###...",
                         "......######...........###..................######...........###............###...................###.............###...",
                         "###......###...........###............###......###...........###............###...................###.............###...",
                         ".###########...........###.............###########...........###............##############........###.............###...",
                         "...########............###...............########............###............##############........###.............###...",
                       };

void setup() { 
  for( int i = 0; i < PIN_NUM; ++i )
    pinMode( PinTab[i], OUTPUT ); 
}

void loop() {
  for( int i = 0; i < COLUMNS; ++i ){
    for( int j = 0; j <= PIN_NUM; ++j){
      digitalWrite( PinTab[j], ( wordTab[ j ][ i ] == '#')? HIGH : LOW  );
    }
    delay( STEP_TIME );
  }
}
