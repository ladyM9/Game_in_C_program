
#include "Adafruit_GFX.h"
#include "ILI9341_STM32.h"

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

typedef struct myline {
  int16_t x0;
  int16_t y0;
  int16_t x1;
  int16_t y1;
} myline_t;


struct OBJECT {
  int x = 1;
  int y = 1;
  int r = 5;


} OBJECT1;

struct LINE {
  int m = 162;
  int n = 238;
  int m1 = 188;
  int n1 = 239;
} LINE1;


struct OD {
  int X = 10;
  int Y = 10;
  int h = 8;
  int w = 8;
} OD1;

const myline_t myLab1[] = {{2, 1, 128, 1} , {163, 1, 318, 1} , {318, 1, 318, 239} , {318, 239, 193, 239} , {158, 238, 1, 239}, {1, 239, 2, 1}, {128, 1, 128, 48} , {128, 48, 74, 48} , {74, 48, 74, 25}, {74, 25, 40, 25} , {160, 25, 160, 73} , {160, 73, 35, 73} , {35, 73, 34, 48} , {81, 73, 81, 96}, {1, 96, 35, 96} , {128, 120, 35, 120} , {128, 143, 97, 144} , {1, 144, 65, 144} , {65, 144, 65, 214} , {65, 168, 97, 168} , {101, 192, 127, 192}, {1, 191, 33, 191}, {33, 214, 96, 214}, {127, 97, 127, 239}, {128, 97, 192, 97} , {192, 96, 192, 48} , {192, 48, 161, 48} , {196, 25, 223, 25} , {224, 1, 224, 50} , {192, 71, 255, 71} , {255, 71, 255, 49} , {255, 49, 286, 49} , {286, 49, 286, 25} , {286, 25, 259, 25}, {286, 72, 286, 143} , {286, 96, 222, 96} , {222, 96, 222, 119} , {222, 119, 159, 119} , {159, 119, 159, 213} , {159, 143, 192, 143} , {191, 167, 319, 167}, {222, 167, 222, 144}, {255, 120, 255, 189}, {159, 190, 222, 190} , {222, 190, 222, 214} , {222, 214, 284, 214},
  {285, 191, 319, 191} , {161, 214, 192, 214} , {192, 214, 192, 235}
};
//const myline_t myLab1[] = {{1, 4, 11, 4} , {19, 1, 19, 8}, {11, 8, 19, 8} , {11, 9, 11, 17} , {1, 22, 11, 22} , {11, 26, 18, 26} , {11, 27, 11, 31} , {1, 36, 10, 36} , {19, 13, 19, 39 }, {11, 40, 33, 40} , {20, 8, 24, 8} , {28, 4, 33, 4} , {34, 1, 34, 17}, {20, 13, 25, 13}, {28, 18, 34, 18} , {27, 19, 27, 29} , {27, 27, 34, 27}, {34, 28, 34, 31}, {20, 36, 48, 36}, {36, 22, 41, 22}, {42, 5, 42 , 35}, {49, 6, 49, 8}, {65, 5, 65, 8} , {73, 1, 73, 3}, {50, 8, 83, 8}, {43, 13, 48, 13}, {57, 9, 57, 18} , {50, 18, 57, 18} , {43, 26, 56, 26} , {57, 22, 57, 26} , {58, 22, 65, 22} , {65, 18, 65, 22} , {66, 18, 72, 18} , {72, 13, 72, 18} , {65, 13, 72, 13} , {74, 23, 74, 26} , {65, 23, 73, 23}, {53, 31, 73, 31} , {73, 31, 73, 39} , {57, 40, 73, 40}, {49, 37, 49, 47}, {42, 40, 42, 47}, {65, 41, 65, 47}};
const myline_t myLab2[] = {{1, 0, 81, 0}, {0, 0, 0, 46}, {81, 0, 81, 46}, {0, 47, 42, 47}, {49, 47, 83, 47}};
const myline_t myLab3[] = {42, 48, 49, 48}; //linija za izlaz
const myline_t myLab4[] = {{0, 0, 99, 0 } , {126, 0, 249, 0} , {0, 0, 0, 141} , {0, 141, 123, 141} , {150, 141, 249, 141}, {249, 141, 249, 0} , {1, 27, 18, 27} , {27, 15, 48, 15} , {51, 15, 51, 42}, {24, 42, 17, 42} , {24, 42, 24, 69} , {24, 69, 51, 69}, {51, 69, 51, 126}, {3, 84, 24, 84}, {84, 84, 24, 111}, {75, 3, 75, 81}, {57, 57, 72, 57} , {54, 99, 96, 99} , {75, 114, 75, 138} , {99, 15, 99, 141}, {102, 27, 150, 27} , {150, 27, 150, 42}, {126, 42, 150, 42} , {126, 36, 126, 54} , {174, 15, 174, 57} , {153, 57, 174, 57}, {150, 57, 150, 69}, {141, 69, 150, 69}, {177, 42, 198, 42}, {99, 3, 99, 42}, {225, 15, 225, 69} , {201, 84, 225, 69}, {99, 66, 198, 99}, {225, 84, 225, 84} , {126, 84, 195, 84} , {126, 84, 126, 111}, {198, 99, 222, 99} , {102, 114, 147, 114} , {150, 99, 174, 99}, {174, 99, 174, 114}, {174, 114, 249, 114}, {135, 129, 198, 129}, {147, 129, 147, 141}};
const myline_t *myLabs[] = {myLab1 , myLab2, myLab3, myLab4};
void setup() {
  // put your setup code here, to run once:
  pinMode(1, INPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  Serial.begin(115200);
  display.begin();
  display.setRotation(1);
  display.clearDisplay();
  display.setTextWrap(false);
  display.setTextSize(4);
  //  display.setContrast(50);
  display.setCursor(0, 0);
  display.setTextColor(ILI9341_BLUE);
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
  //mapx = map(locationx, 0 , 1023, 0, 319);
  //mapy = map(locationy, 0 , 1023, 0, 239);

  if (rawX < 500 || rawX > 520) {
    OBJECT1.x += (511 - rawX) / 100;
    if (OBJECT1.x > 319) OBJECT1.x = 319;
    if (OBJECT1.x < 0) OBJECT1.x = 0;
    ref = true;

  }
  if (rawY < 500 || rawY > 520) {
    OBJECT1.y += (511 - rawY) / 100;

    if (OBJECT1.y > 239) OBJECT1.y = 239;
    if (OBJECT1.y < 0) OBJECT1.y = 0;
    ref = true;
  }
  if (ref) {
    ref = false;
    display.clearDisplay();
    //    odabir_lab(x, OD1, OBJECT1);
    display.fillCircle(OBJECT1.x, OBJECT1.y, OBJECT1.r , ILI9341_WHITE);
    for ( int i = 0 ; i < 49 ; i++) //petlja za iscrtavanje svih linija u labirintu
    {
      display.drawLine(myLabs[0][i].x0, myLabs[0][i].y0, myLabs[0][i].x1, myLabs[0][i].y1, ILI9341_WHITE);
      //display.drawLine(myLabs[1][i].x0, myLabs[1][i].y0, myLabs[1][i].x1, myLabs[1][i].y1, ILI9341_BLACK);
    }
    display.display();
//      if (collided_with(OBJECT1, LINE1)) {  //ako se dogodila kolizija odnosno ako je kuglica na izlazu iz laba napravi sljedeće
//        display.clearDisplay();
//  //      display.setTextWrap(false);
//  //      display.setTextSize(4);
//        display.setCursor(0, 0);
//        display.setRotation(1);
//        display.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
//  //      display.print("YOU WON " );
//       //display.display();
//        while (true);
//    }
    

  }
}
//bool collided_with(struct OBJECT o, struct LINE l) {
//  //  funkcija za detekciju kolizije
//  int i ;
//  bool _collisionDetected = false;
//
//    for (int i = 0; i < 49; i++)
//    {
//      if ((OBJECT1.x && OBJECT1.y) >= i) _collisionDetected = true;
//      if (_collisionDetected) {
//        return true;
//      }
//  
//    }  
//}
 // for ( int i = 0 ; i < 49 ; i++) {
//    const myline_t myLab1[]; 
    
  
//    if((o.x =  myLabs[i][i]) && (o.y =  myLabs[i][i])) &&  _collisionDetected = true;
//     if( _collisionDetected) {
//      o.x -=2;
//      o.y -=2;
//      return true;
//    } 
//
//    else {
//      return false;
//    }
//    }
//  
//
//    if ((o.x >= l.m) && (o.x >= l.m1) && (o.y >= l.n) && (o.y  >= l.n1)) _collisionDetected = true;  //detekcija na izlaz iz labirinta
//    if (_collisionDetected ) {
//
//      return true;
//    }
//    else{
//      return false;
//    }
//  //}
//}
  

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
