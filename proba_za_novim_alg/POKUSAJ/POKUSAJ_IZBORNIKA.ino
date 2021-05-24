
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
int x;
int SW = 2;
int SW_state = 0;


bool ref = false;

typedef struct myline {
  int16_t x0;
  int16_t y0;
  int16_t x1;
  int16_t y1;
} myline_t;

+
struct OBJECT {
  int x = 1;
  int y = 1;
  int r = 1;


} OBJECT1;

struct LINE {
  int m = 42;
  int n = 48;
  int m1 = 49;
  int n1 = 48;
} LINE1;


struct OD {
  int X = 10;
  int Y = 10;
  int h = 8;
  int w = 8;
} OD1;


const myline_t myLab1[] = {{1, 4, 11, 4} , {19, 1, 19, 8}, {11, 8, 19, 8} , {11, 9, 11, 17} , {1, 22, 11, 22} , {11, 26, 18, 26} , {11, 27, 11, 31} , {1, 36, 10, 36} , {19, 13, 19, 39 }, {11, 40, 33, 40} , {20, 8, 24, 8} , {28, 4, 33, 4} , {34, 1, 34, 17}, {20, 13, 25, 13}, {28, 18, 34, 18} , {27, 19, 27, 29} , {27, 27, 34, 27}, {34, 28, 34, 31}, {20, 36, 48, 36}, {36, 22, 41, 22}, {42, 5, 42 , 35}, {49, 6, 49, 8}, {65, 5, 65, 8} , {73, 1, 73, 3}, {50, 8, 83, 8}, {43, 13, 48, 13}, {57, 9, 57, 18} , {50, 18, 57, 18} , {43, 26, 56, 26} , {57, 22, 57, 26} , {58, 22, 65, 22} , {65, 18, 65, 22} , {66, 18, 72, 18} , {72, 13, 72, 18} , {65, 13, 72, 13} , {74, 23, 74, 26} , {65, 23, 73, 23}, {53, 31, 73, 31} , {73, 31, 73, 39} , {57, 40, 73, 40}, {49, 37, 49, 47}, {42, 40, 42, 47}, {65, 41, 65, 47}};
const myline_t myLab2[] = {{1, 0, 81, 0}, {0, 0, 0, 46}, {81, 0, 81, 46}, {0, 47, 42, 47}, {49, 47, 83, 47}};
const myline_t myLab3[] = {42, 48, 49, 48}; //linija za izlaz
const myline_t myLab4[] = {{0, 0, 33, 0 } , {42, 0, 83, 0} , {0, 0, 0, 47} , {0, 47, 41, 47} , {50, 47, 83, 47}, {83, 47, 83, 0} , {1, 9, 6, 9} , {9, 5, 16, 5} , {17, 5, 17, 14}, {8, 14, 17, 14} , {8, 14, 8, 23} , {8, 23, 17, 23}, {17, 23, 17, 42}, {1, 28, 8, 28}, {8, 28, 8, 37}, {25, 1, 25, 27}, {19, 19, 24, 19} , {18, 33, 32, 33} , {25, 38, 25, 46} , {33, 5, 33, 47}, {34, 9, 50, 9} , {50, 9, 50, 14}, {42, 14, 50, 14} , {42, 12, 42, 18} , {58, 5, 58, 19} , {51, 19, 58, 19}, {50, 19, 50, 23}, {47, 23, 50, 23}, {59, 14, 66, 14}, {66, 1, 66, 14}, {75, 5, 75, 23} , {67, 23, 75, 23}, {66, 22, 66, 33}, {75, 28, 82, 28} , {42, 28, 65, 28} , {42, 28, 42, 37}, {66, 33, 74, 33} , {34, 38, 49, 38} , {50, 33, 58, 33}, {58, 33, 58, 38}, {58, 38, 83, 38}, {45, 43, 66, 43}, {49, 43, 49, 47}};
const myline_t *myLabs[] = {myLab1 , myLab2, myLab3, myLab4};
void setup() {
  // put your setup code here, to run once:
  pinMode(1, INPUT);

  Serial.begin(115200);
  display.begin();
  display.clearDisplay();
  display.setTextWrap(false);
  display.setContrast(50);
  display.setCursor(0, 0);
  display.setTextColor(BLACK);
  OBJECT1.x = display.width() / 2; // gdje iscrtati krug po x osi
  OBJECT1.y = display.height() / 2; // gdje iscrtati krug po y osi


  Serial.println(myLabs[1][1].x0, DEC);
  display.display();


}

void loop() {
  // put your main code here, to run repeatedly:
  int rawX = 1023 - analogRead(A0);
  int rawY = 1023 - analogRead(A1);

  //  OBJECT1.w = digitalRead(D2);
  //mapx = map(locationx, 0 , 1023, 0, 83);
  //mapy = map(locationy, 0 , 1023, 0, 47);

  if (rawX < 500 || rawX > 520) {
    OBJECT1.x += (511 - rawX) / 50;
    if (OBJECT1.x > 83) OBJECT1.x = 83;
    if (OBJECT1.x < 0) OBJECT1.x = 0;
    ref = true;

  }
  if (rawY < 500 || rawY > 520) {
    OBJECT1.y += (511 - rawY) / 50;

    if (OBJECT1.y > 47) OBJECT1.y = 47;
    if (OBJECT1.y < 0) OBJECT1.y = 0;
    ref = true;
  }
  if (ref) {
    ref = false;
    display.clearDisplay();
    //    odabir_lab(x, OD1, OBJECT1);
    display.fillCircle(OBJECT1.x, OBJECT1.y, OBJECT1.r , BLACK);
    for ( int i = 0 ; i < 49 ; i++) //petlja za iscrtavanje svih linija u labirintu
    {
      display.drawLine(myLabs[3][i].x0, myLabs[3][i].y0, myLabs[3][i].x1, myLabs[3][i].y1, BLACK);
      //display.drawLine(myLabs[1][i].x0, myLabs[1][i].y0, myLabs[1][i].x1, myLabs[1][i].y1, BLACK);
    }
    display.display();
    if (collided_with(OBJECT1, LINE1)) {  //ako se dogodila kolizija odnosno ako je kuglica na izlazu iz laba napravi sljedeće
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextColor(BLACK, WHITE);
      display.print("YOU WON " );
      display.display();
      while (true);
    }
    display.display();

  }
}
bool collided_with(struct OBJECT o, struct LINE l) {
//  funkcija za detekciju kolizije
  int i ;
  bool _collisionDetected = false;

  //  for (int i = 0; i < 49; i++)
  //  {
  //    if ((OBJECT1.x && OBJECT1.y) >= i) _collisionDetected = true;
  //    if (_collisionDetected) {
  //      return true;
  //    }
  //
  //  }
  for( int i = 0 ; i < 4 ; i++) {
  
  if ((o.x == (l.m) && (o.x == l.m1)) && (o.y == (l.n || l.n1))) _collisionDetected = true;  //detekcija na izlaz iz labirinta
  if (_collisionDetected ) {
    
    return true;
  }
  }

  return false;

  //display.display();
  //    if (analogRead(A0)) {
  //      display.clearDisplay();
  //    }
  //
  //    while (true);
  //  }
}

//bool odabir_game(int x, struct OD t, struct OBJECT o) { //funkcija koja će biti za odabir igrice
//  display.clearDisplay();
//  display.setCursor(0, 0);
//  display.setTextColor(BLACK, WHITE);
//  display.print("ODABERI IGRICU " );
//  display.drawRect(10, 10, 8, 8, BLACK);
//  int rawX = 1023 - analogRead(A0);
//  int rawY = 1023 - analogRead(A1);
//  OBJECT1.x = display.width() / 2; // gdje iscrtati krug po x osi
//  OBJECT1.y = display.height() / 2; // gdje iscrtati krug po y osi
//
//  display.fillCircle(OBJECT1.x, OBJECT1.y, OBJECT1.r , BLACK);
//
//  display.display();
//
//  if (digitalRead(D1) == (t.X)) {
//
//  }
//}
