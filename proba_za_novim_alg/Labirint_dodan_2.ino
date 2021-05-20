
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
int rectw = 40; //duljina stranice kv
int recth = 40;//visina stranice kv
int rectlocx = 0; //lokacija po x osi od kvadrata
int rectlocy = 0; //

bool ref = false;

typedef struct myline {
  int16_t x0;
  int16_t y0;
  int16_t x1;
  int16_t y1;
} myline_t;

struct RECT {
  int rectw = 40;
  int recth = 40;
  int rectlocx = 0; //width od kvadrata
  int rectlocy = 0; //
  int distance = 0;
} RECT1;


struct OBJECT {
  int x = 1;
  int y = 1;
  int r = 2;


} OBJECT1;

struct LINE {
  int m = 42;
  int n = 48;
  int m1 = 49;
  int n1 = 48;
} LINE1;

struct DISTANCE {
  int a = 0;
  int b = 0;
  int a1 = 0;
  int b1 = 0;
} DISTANCE1;


const myline_t myLab1[] = {{1, 4, 11, 4} , {19, 1, 19, 8}, {11, 8, 19, 8} , {11, 9, 11, 17} , {1, 22, 11, 22} , {11, 26, 18, 26} , {11, 27, 11, 31} , {1, 36, 10, 36} , {19, 13, 19, 39 }, {11, 40, 33, 40} , {20, 8, 24, 8} , {28, 4, 33, 4} , {34, 1, 34, 17}, {20, 13, 25, 13}, {28, 18, 34, 18} , {27, 19, 27, 29} , {27, 27, 34, 27}, {34, 28, 34, 31}, {20, 36, 48, 36}, {36, 22, 41, 22}, {42, 5, 42 , 35}, {49, 6, 49, 8}, {65, 5, 65, 8} , {73, 1, 73, 3}, {50, 8, 83, 8}, {43, 13, 48, 13}, {57, 9, 57, 18} , {50, 18, 57, 18} , {43, 26, 56, 26} , {57, 22, 57, 26} , {58, 22, 65, 22} , {65, 18, 65, 22} , {66, 18, 72, 18} , {72, 13, 72, 18} , {65, 13, 72, 13} , {74, 23, 74, 26} , {65, 23, 73, 23}, {53, 31, 73, 31} , {73, 31, 73, 39} , {57, 40, 73, 40}, {49, 37, 49, 47}, {42, 40, 42, 47}, {65, 41, 65, 47}};
const myline_t myLab2[] = {{1, 0, 81, 0}, {0, 0, 0, 46}, {81, 0, 81, 46}, {0, 47, 42, 47}, {49, 47, 83, 47}};
const myline_t myLab3[] = {42, 48, 49, 48}; //linija za izlaz
const myline_t myLab4[] = {{0, 0, 33, 0 } , {42, 0, 83, 0} , {0, 0, 0, 47} , {0, 47, 41, 47} , {50, 47, 83, 47}, {83, 47, 83, 0} , {1, 9, 6, 9} , {9, 5, 16, 5} , {17, 5, 17, 14}, {8, 14, 17, 14} , {8, 14, 8, 23} , {8, 23, 17, 23}, {17, 23, 17, 42}, {1, 28, 8, 28}, {8, 28, 8, 37}, {25, 1, 25, 27}, {19, 19, 24, 19} , {18, 33, 32, 33} , {25, 38, 25, 46} , {33, 5, 33, 47}, {34, 9, 50, 9} , {50, 9, 50, 14}, {42, 14, 50, 14} , {42, 12, 42, 18} , {58, 5, 58, 19} , {51, 19, 58, 19}, {50, 19, 50, 23}, {47, 23, 50, 23}, {59, 14, 66, 14}, {66, 1, 66, 14}, {75, 5, 75, 23} , {67, 23, 75, 23}, {66, 22, 66, 33}, {75, 28, 82, 28} , {42, 28, 65, 28} , {42, 28, 42, 37}, {66, 33, 74, 33} , {34, 38, 49, 38} , {50, 33, 58, 33}, {58, 33, 58, 38}, {58, 38, 83, 38}, {45, 43, 66, 43}, {49, 43, 49, 47}};
const myline_t *myLabs[] = {myLab1 , myLab2, myLab3, myLab4};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  display.begin();
  display.clearDisplay();
  display.setTextWrap(false);
  display.setContrast(50);
  display.setCursor(0, 0);
  display.setTextColor(BLACK);
  RECT1.rectlocx = (display.width() / 2 ) - (rectw / 2 ); // gdje iscrtati kvadrat po x osi
  RECT1.rectlocy = (display.height() / 2) - (recth / 2); // gdje iscrtati kvadrat po y osi
  OBJECT1.x = display.width() / 2; // gdje iscrtati krug po x osi
  OBJECT1.y = display.height() / 2; // gdje iscrtati krug po y osi


  Serial.println(myLabs[1][1].x0, DEC);
  //  display.drawRect(0, 0 , 84 , 48, BLACK);
  //display.fillCircle(1, 1, OBJECT1.r , BLACK);
  //
  //  for ( int i = 0 ; i < 44 ; i++)
  //  {
  //    display.drawLine(myLabs[0][i].x0, myLabs[0][i].y0, myLabs[0][i].x1, myLabs[0][i].y1, BLACK);
  //    //display.drawLine(myLabs[1][i].x0, myLabs[1][i].y0, myLabs[1][i].x1, myLabs[1][i].y1, BLACK);
  //  }
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
    //    display.drawLine(0, 15, 100, 25, BLACK);
    //    display.drawLine(20, 5, 100, 10, BLACK);
    display.fillCircle(OBJECT1.x, OBJECT1.y, OBJECT1.r , BLACK);
    // display.drawRect(0, 0 , 84 , 48, BLACK);
    for ( int i = 0 ; i < 49 ; i++)
    {
      display.drawLine(myLabs[3][i].x0, myLabs[3][i].y0, myLabs[3][i].x1, myLabs[3][i].y1, BLACK);
      //display.drawLine(myLabs[1][i].x0, myLabs[1][i].y0, myLabs[1][i].x1, myLabs[1][i].y1, BLACK);
    }
    display.display();
    if (collided_with(OBJECT1, RECT1, DISTANCE1 , LINE1)) {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextColor(BLACK, WHITE);
      display.print("YOU WON " );
      display.display();
      while (true);
    }
    display.display();
//    if (collided_with(OBJECT1, RECT1, DISTANCE1 , LINE1)) {
//      OBJECT1.x -= 2;
//      OBJECT1.y -=2;
//      display.display();
//      while (true);
//    }
//    display.display();

  }
}
bool collided_with(struct OBJECT o, struct RECT r, struct  DISTANCE d, struct LINE l) {
  d.a = abs(o.x - r.rectlocx);  // krug je za x udaljen od središta pravokutnika po x osi odnosno horizontalnoj
  d.b = abs(o.y - r.rectlocy);
  d.a1 = abs(o.x + r.rectlocx);
  d.b1 = abs (o.y + r.rectlocy);
  int i ;
  //if ((d.m > ( r.rectw  + o.r/2)) || (d.n > (r.recth  + o.r/2)) && (d.m  <=  (r.rectw) ||  (d.n <= (r.recth))) || ( d.e < ( r.recth + o.r/2)) && ( d.t < (r.rectw + o.r/2))){
  // cDist_sq = (distance.x - r.rectw / 2) ^ 2 + (distance.y - r.recth / 2) ^ 2;
  //if (cDist_sq <=  (o.r^2)) {
  bool _collisionDetected = false;
  bool _collisionDetected1 = false;

  for (int i = 0; i < 49; i++)
  {
    if ((OBJECT1.x && OBJECT1.y) >= i) _collisionDetected1 = true;
    if (_collisionDetected) {
      return true;
    }

  }

  if ((OBJECT1.x >= (l.m) && (OBJECT1.x >= l.m1)) && (OBJECT1.y >= (l.n || l.n1))) _collisionDetected = true;
  if (_collisionDetected ) {
    //display.clearDisplay();
    //display.setCursor(0, 0);
    //display.setTextColor(BLACK, WHITE);
    //display.print("YOU WON " );
    //display.display();
    return true;
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
