#include <Adafruit_PCD8544.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
int x = 0;
int y = 0;
int w = 0;
int mapx = 0;
int mapy = 0;
int locationx = 0;
int locationy = 0;
bool ref = false;
int rectw = 40; //duljina stranice kv
int recth = 40;//visina stranice kv
int rectlocx = 0; //lokacija po x osi od kvadrata
int rectlocy = 0; //
bool collision = false;
int distance = 0;
int cDist_sq = 0;
int n1 = 30;
int m1 = 13;
int n2 = 50;
int m2 = 13;

int n3 = 30;
int m3 = 13;
int n4 = 30;
int m4 = 23;

int n5 = 30;
int m5 = 23;
int n6 = 37;
int m6 = 23;

int n7 = 45;
int m7 = 23;
int n8 = 60;
int m8 = 23;

int n9 = 37;
int m9 = 37;
int n10 = 37;
int m10 = 44;

int n11 = 44;
int m11 = 44;
int n12 = 55;
int m12 = 44;


//char CollisionDect(int rectlocx, int rectlocy, int recth, int rectw, int locationx, int locationy, int x, int y);
char rect;
struct OBJECT {
  int x;
  int y;
  int r = 2;


} OBJECT1;

struct RECT {
  int rectw = 40;
  int recth = 40;
  int rectlocx = 0; //width od kvadrata
  int rectlocy = 0; //
  int distance = 0;
} RECT1;

struct DISTANCE {
  int m = 0;
  int n = 0;
  int e = 0;
  int t = 0;
} DISTANCE1;

struct LINE {
  int n1 = 30;
  int m1 = 13;
  int n2 = 50;
  int m2 = 13;

  int n3 = 30;
  int m3 = 13;
  int n4 = 30;
  int m4 = 23;

  int n7 = 30;
  int m7 = 23;
  int n8 = 65;
  int m8 = 23;



} LINE1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  display.begin();
  OBJECT1.x = display.width() / 2; // gdje iscrtati krug po x osi
  OBJECT1.y = display.height() / 2; // gdje iscrtati krug po y osi
  RECT1.rectlocx = (display.width() / 2) - (rectw / 2); // gdje iscrtati kvadrat po x osi
  RECT1.rectlocy = (display.height() / 2) - (recth / 2); // gdje iscrtati kvadrat po y osi

  pinMode(USER_BTN, INPUT_PULLDOWN);
  pinMode(D2, INPUT_PULLUP);
  //int Tipka = 0;
  display.setTextWrap(false);
  display.setContrast(50);
  display.clearDisplay(); //brise sve u RAM-u, to se zove frame buffer, ima cijelu kopiju slike sa zaslona u ramu, brise iz rama ali na ekranu sve ostaje
  display.display(); //salje cijelu sliku na ekran
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setTextColor(WHITE);
  display.println("Marina");
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
    display.drawLine(n1, m1, n2, m2, BLACK);
    display.drawLine (n3 , m3, n4, m4 , BLACK);
    display.drawLine (n5 , m5, n6 , m6, BLACK);
    display.drawLine ( n7, m7, n8 , m8 , BLACK);
    display.drawLine ( n9, m9, n10, m10, BLACK);
    display.drawLine (n11, m11, n12, m12, BLACK);
    display.drawRect(RECT1.rectlocx, RECT1.rectlocy , RECT1.rectw , RECT1.recth, BLACK);
    //display.drawLine(5, 10, 30, 25, BLACK);
    display.display();
    //rect = CollisionDect(rectlocx, rectlocy, recth, rectw, locationx, locationy, x, y);
    delay(100);
    collided_with(OBJECT1, RECT1, DISTANCE1, LINE1);
    //delay(1000);
    display.display();
  }

}
void collided_with(struct OBJECT o, struct RECT r, struct  DISTANCE d, struct LINE l) {
  d.m = abs(o.x - r.rectlocx);  // krug je za x udaljen od središta pravokutnika po x osi odnosno horizontalnoj
  d.n = abs(o.y - r.rectlocy);
  d.e = abs(o.x + r.rectlocx);
  d.t = abs (o.y + r.rectlocy);
  //if ((d.m > ( r.rectw  + o.r/2)) || (d.n > (r.recth  + o.r/2)) && (d.m  <=  (r.rectw) ||  (d.n <= (r.recth))) || ( d.e < ( r.recth + o.r/2)) && ( d.t < (r.rectw + o.r/2))){
  // cDist_sq = (distance.x - r.rectw / 2) ^ 2 + (distance.y - r.recth / 2) ^ 2;
  //if (cDist_sq <=  (o.r^2)) {
  bool _collisionDetected = false;
  if (o.y == r.rectlocy && (o.x > r.rectlocx) && (o.x < (r.rectlocx + r.rectw))) _collisionDetected = true;
  if (o.y == (r.rectlocy + r.recth) && (o.x > r.rectlocx) && (o.x < (r.rectlocx + r.rectw))) _collisionDetected = true;
  if (o.x > r.rectlocx && ( o.x < r.rectlocx + r.rectw) && ( o.y == r.rectlocy || o.y == r.rectlocy + r.recth)) _collisionDetected = true;
  if ( o.y > r.rectlocy && (o.y < r.rectlocy + r.recth) && ( o.x == r.rectlocx || o.x == r.rectlocx + r.rectw)) _collisionDetected = true;
  if (( o.y == l.m1  && (o.x > l.n1)) && (o.x < (l.n2 + l.m2)) && (o.y == l.m2) ) _collisionDetected = true;
  if (( o.x > l.n3 && ( o.x < l.n3)) && (o.y == (l.m3 + l.m3 )) && (o.y == l.m3)) _collisionDetected = true;
  if (_collisionDetected) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(BLACK, WHITE);
    display.print("Game over " );
    display.display();
    if (analogRead(A0)) {
      display.clearDisplay();
    }

    while (true);
  }
}

//
//  if ((o.x == (r.rectlocx+10) )  && (o.y == (r.rectlocy+5)) || (o.x == (r.rectlocx+15)))  {
//    display.clearDisplay();
//    display.setCursor(0, 0);
//    display.setTextColor(BLACK, WHITE);
//    display.print("Game over " );
//    display.display();
//while (true);




//  if(digitalRead(USER_BTN) == true) {
//    display.print("Tipka pritisnuta");
//  }
//  else {
//    display.print("Tipka nije pritisnuta");
//
//  display.print(digitalRead(USER_BTN) ? "Tipka pritisnuta" : "Tipka nepritisnuta"); // pomocu kondicionala, dakle ako je USER_BTN true ispiši tipka pritisnuta, inace tipka nepritisnuta
