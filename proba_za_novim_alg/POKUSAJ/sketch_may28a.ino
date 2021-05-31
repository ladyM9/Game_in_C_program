#include "Adafruit_GFX.h"
#include "ILI9341_STM32.h"

#include "MyLabsDefines.h"

#define TFT_DC 9
#define TFT_CS 10
Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC);

//#include <SPI.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_PCD8544.h>
//Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
int x;
int SW = 2;
int SW_state = 0;
bool ref = false;

struct OBJECT {
  int x = 140;
  int y = 1;
  int r = 5;


} OBJECT1;

struct STARTL {
  int x = 1;
  int y = 128;
  int x1 = 1;
  int y1 = 163;
} STARTL1;

struct LINE {
  int x = 162;
  int y = 238;
  int x1 = 188;
  int y1 = 239;
} LINE1;

void setup() {
  // put your setup code here, to run once:
  pinMode(1, INPUT);

  Serial.begin(115200);
  display.begin();
  display.setRotation(1);
  display.clearDisplay();
  display.setTextWrap(false);
  display.setTextSize(4);
  //  display.setContrast(50);
  display.setCursor(0, 0);
  display.setTextColor(ILI9341_BLUE);
  //  OBJECT1.x = display.width() / 2; // gdje iscrtati krug po x osi
  //  OBJECT1.y = display.height() / 2; // gdje iscrtati krug po y osi


  Serial.println(myLabs[1][1].x0, DEC);
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  int rawX = 1023 - analogRead(A0);
  int rawY = 1023 - analogRead(A1);

  //  OBJECT1.w = digitalRead(D2);
  //mapx = map(locationx, 0 , 1023, 0, 319);
  //mapy = map(locationy, 0 , 1023, 0, 239);

  if (rawX < 500 || rawX > 520) {
    OBJECT1.x += (511 - rawX) / 50;
    if (OBJECT1.x > 319) OBJECT1.x = 319;
    if (OBJECT1.x < 0) OBJECT1.x = 0;
    ref = true;

  }
  if (rawY < 500 || rawY > 520) {
    OBJECT1.y += (511 - rawY) / 50;

    if (OBJECT1.y > 239) OBJECT1.y = 239;
    if (OBJECT1.y < 0) OBJECT1.y = 0;
    ref = true;
  }
  if (ref) {
    ref = false;
    int rezult;
    display.clearDisplay();
    //    odabir_lab(x, OD1, OBJECT1);
    display.fillCircle(OBJECT1.x, OBJECT1.y, OBJECT1.r , ILI9341_WHITE);
    for ( int i = 0 ; i < 49 ; i++) //petlja za iscrtavanje svih linija u labirintu
    {
      display.drawLine(myLabs[0][i].x0, myLabs[0][i].y0, myLabs[0][i].x1, myLabs[0][i].y1, ILI9341_WHITE);
      //display.drawLine(myLabs[1][i].x0, myLabs[1][i].y0, myLabs[1][i].x1, myLabs[1][i].y1, ILI9341_BLACK);
    }
    display.display();
    if (rezult  =(collided_with(OBJECT1, LINE1, myLabs[1]))) {  //ako se dogodila kolizija odnosno ako je kuglica na izlazu iz laba napravi sljedeće
      display.clearDisplay();
      display.setTextWrap(false);
      display.setTextSize(4);
      display.setCursor(0, 0);
      display.setRotation(1);
      display.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
      display.print("YOU WON " );
      display.display();
      while (true);
    }
    if (rezult = (collided_with(OBJECT1, LINE1, myLabs[1]))) {
      OBJECT1.x -= 2;
      OBJECT1.y -= 2;
      while(true);
    }
  }
}
int collided_with(struct OBJECT o, struct LINE l,  const myline_t *v) {
  //  funkcija za detekciju kolizije
  int rez ;
  bool _collisionDetected = false;

  //  for (int i = 0; i < 49; i++)
  //  {
  //    if ((OBJECT1.x && OBJECT1.y) >= i) _collisionDetected = true;
  //    if (_collisionDetected) {
  //      return true;
  //    }
  //
  //  }
  //  for ( int i = 0 ; i < 49 ; i++) {
  //    const myline_t myLab1[];


  if ((o.x = v->x0) && (o.x = v->x1) && (o.y = v->y0) && (o.y = v->y1)) _collisionDetected = true;
  if ( _collisionDetected) {
    return 0;
  }else{
    return false;
  }

  if ((o.x >= l.x) && (o.x <= l.x1) && (o.y >= l.y) && (o.y  <= l.y1)) _collisionDetected = true;  //detekcija na izlaz iz labirinta
  if (_collisionDetected ) {
    return 1;
  }else{
    return false;
  }

}
//display.display();
//    if (analogRead(A0)) {
//      display.clearDisplay();
//    }
//
//    while (true);
//  }
//}

//bool odabir_game(int x, struct OD t, struct OBJECT o) { //funkcija koja će biti za odabir igrice
//  display.clearDisplay();
//  display.setCursor(0, 0);
//  display.setTextColor(ILI9341_BLACK, ILI9341_WHITE);
//  display.print("ODABERI IGRICU " );
//  display.drawRect(10, 10, 8, 8, ILI9341_BLACK);
//  int rawX = 1023 - analogRead(A0);
//  int rawY = 1023 - analogRead(A1);
//  OBJECT1.x = display.width() / 2; // gdje iscrtati krug po x osi
//  OBJECT1.y = display.height() / 2; // gdje iscrtati krug po y osi
//
//  display.fillCircle(OBJECT1.x, OBJECT1.y, OBJECT1.r , ILI9341_BLACK);
//
//  display.display();
//
//  if (digitalRead(D1) == (t.X)) {
//
//  }
//}
