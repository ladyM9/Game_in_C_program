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
int z = 0;


bool ref = false;
bool time_game = false;

typedef struct myline {
  int16_t x0;
  int16_t y0;
  int16_t x1;
  int16_t y1;
} myline_t;    // moje linije u labirintu dakle x0, yo početne točke, a x1, i y1 krajnje točke


struct OBJECT {
  int x ;
  int y ;
  int xOld ;
  int yOld ;
  int r = 2;
  int O = 2 * r * 3.14;
} OBJECT1;

struct izl {
  int m0 = 128;
  int n0 = 5;
  int m1 = 163;
  int n1 = 5;
} izl_1;

//struct LINE {
//  int m = 162;
//  int n = 238;
//  int m1 = 188;
//  int n1 = 239;
//}, LINE1;


//struct OD {
//  int X = 10;
//  int Y = 10;
//  int h = 8;
//  int w = 8;
//} OD1;

struct triangle {
  int x0 = 20;
  int y0 = 55;
  int x1 = 75;
  int y1 = 90;
  int x2 = 100;
  int y2 = 112;
} TRIANGLE_1;


struct triangle1 {
  int x0 = 150;
  int y0 = 165;
  int x1 = 170;
  int y1 = 200;
  int x2 = 210;
  int y2 = 219;
} TRIANGLE_2;

const myline_t myLab1[] = {{2, 1, 128, 1}, {163, 1, 318, 1}, {318, 1, 318, 239}, {318, 239, 193, 239}, {158, 238, 1, 239}, {1, 239, 2, 1}, {128, 1, 128, 48}, {128, 48, 74, 48}, {74, 48, 74, 25}, {74, 25, 40, 25}, {160, 25, 160, 73}, {160, 73, 35, 73}, {35, 73, 34, 48}, {81, 73, 81, 96}, {1, 96, 35, 96}, {128, 120, 35, 120}, {128, 143, 97, 144}, {1, 144, 65, 144}, {65, 144, 65, 214}, {65, 168, 97, 168}, {101, 192, 127, 192}, {1, 191, 33, 191}, {33, 214, 96, 214}, {127, 97, 127, 239}, {128, 97, 192, 97}, {192, 96, 192, 48}, {192, 48, 161, 48}, {196, 25, 223, 25}, {224, 1, 224, 50}, {192, 71, 255, 71}, {255, 71, 255, 49}, {255, 49, 286, 49}, {286, 49, 286, 25}, {286, 25, 259, 25}, {286, 72, 286, 143}, {286, 96, 222, 96}, {222, 96, 222, 119}, {222, 119, 159, 119}, {159, 119, 159, 213}, {159, 143, 192, 143}, {191, 167, 319, 167}, {222, 167, 222, 144}, {255, 120, 255, 189}, {159, 190, 222, 190}, {222, 190, 222, 214}, {222, 214, 284, 214},
  {285, 191, 319, 191}, {161, 214, 192, 214}, {192, 214, 192, 235}
}; // 59 linija imas
//const myline_t myLab1[] = {{1, 4, 11, 4}, {19, 1, 19, 8}, {11, 8, 19, 8}, {11, 9, 11, 17}, {1, 22, 11, 22}, {11, 26, 18, 26}, {11, 27, 11, 31}, {1, 36, 10, 36}, {19, 13, 19, 39 }, {11, 40, 33, 40}, {20, 8, 24, 8}, {28, 4, 33, 4}, {34, 1, 34, 17}, {20, 13, 25, 13}, {28, 18, 34, 18}, {27, 19, 27, 29}, {27, 27, 34, 27}, {34, 28, 34, 31}, {20, 36, 48, 36}, {36, 22, 41, 22}, {42, 5, 42 , 35}, {49, 6, 49, 8}, {65, 5, 65, 8}, {73, 1, 73, 3}, {50, 8, 83, 8}, {43, 13, 48, 13}, {57, 9, 57, 18}, {50, 18, 57, 18}, {43, 26, 56, 26}, {57, 22, 57, 26}, {58, 22, 65, 22}, {65, 18, 65, 22}, {66, 18, 72, 18}, {72, 13, 72, 18}, {65, 13, 72, 13}, {74, 23, 74, 26}, {65, 23, 73, 23}, {53, 31, 73, 31}, {73, 31, 73, 39}, {57, 40, 73, 40}, {49, 37, 49, 47}, {42, 40, 42, 47}, {65, 41, 65, 47},},;
const myline_t myLab2[] = {{2, 2, 66, 2}, {82, 2, 162, 2}, {82, 18, 114, 18}, {130, 18, 162, 18}, {66, 34, 146, 34}, {18, 50, 50, 50}, {82, 50, 98, 50}, {114, 50, 162, 50}, {50, 66, 66, 66}, {98, 66, 146, 66}, {18, 82, 34, 82}, {50, 82, 82, 82}, {146, 82, 162, 82}, {2, 98, 34, 98}, {82, 98, 130, 98}, {146, 98, 162, 98}, {66, 114, 114, 114},  {130, 114, 146, 114}, {50, 130, 66, 130}, {146, 130, 162, 130}, {18, 146, 98, 146},  {130, 146, 146, 146}, {2, 162, 82, 162}, {98, 162, 162, 162},  {2, 2, 2, 162}, {18, 18, 18, 66}, {18, 114, 18, 146}, {34, 2, 34, 34}, {34, 66, 34, 130}, {50, 18, 50, 130}, {66, 18, 66, 50}, {66, 98, 66, 114}, {66, 130, 66, 146}, {82, 2, 82, 18}, {82, 50, 82, 98}, {82, 114, 82, 130}, {82, 146, 82, 162}, {98, 50, 98, 82}, {98, 130, 98, 146}, {114, 34, 114, 50},  {114, 82, 114, 98}, {114, 114, 114, 162}, {130, 66, 130, 82}, {130, 98, 130, 146}, {162, 2, 162, 162}}; //novi lab; //ispravan lab
//const myline_t myLab2[] =  { {3 ,3 ,115 ,3},{143 ,3 ,283 ,3},{143 ,31 ,199 ,31},{227 ,31 ,283 ,31},{115 ,59 ,255 ,59},{31 ,87 ,87 ,87},{143 ,87 ,171 ,87},{199 ,87 ,283 ,87},{87 ,115 ,115 ,115},{171 ,115 ,255 ,115},{1 ,143 ,59 ,143},{87 ,143 ,143 ,143},{255 ,143 ,283 ,143},{3 ,171 ,59 ,171},{143 ,171 ,227 ,171},{255 ,171 ,283 ,171},{115 ,199 ,199 ,199},{227 ,199 ,255 ,199},{87 ,227 ,115 ,227},{255 ,227 ,283 ,227},{31 ,255 ,171 ,255},{227 ,255 ,255 ,255},{3 ,283 ,143 ,283},{171 ,283 ,283 ,283},{3 ,3 ,3 ,283},{31 ,31 ,31 ,115},{31 ,199 ,31 ,255},{59 ,3 ,59 ,59},{59 ,115 ,59 ,227},{87 ,31 ,87 ,227},{115 ,31 ,115 ,87},{115 ,171 ,115 ,199},{115 ,227 ,115 ,255},{143 ,3 ,143 ,31},{143 ,87 ,143 ,171 },{143 ,199 ,143 ,227},{143 ,255 ,143 ,283},{171 ,87 ,171 ,143},{171 ,227 ,171 ,255},{199 ,59 ,199 ,87},{199 ,143 ,199 ,171},{199 ,199 ,199 ,283},{227 ,115 ,227 ,143},{227 ,171 ,227 ,255},{283 ,3 ,283 ,283},},;  //novi lab, 45 LINIJA IMA
const myline_t myLab3[] = {{6 , 6, 102, 6}, {150, 6, 246, 6}, {150, 54, 66, 198}, {6, 102, 198, 102}, {54, 150, 150, 150}, {54, 198, 102, 198}, {198, 198, 246, 198}, {6, 246, 102, 246}, {150, 246, 246, 246}, {6, 6, 6, 246}, {54, 6, 54, 54}, {102, 54, 102, 102}, {102, 198, 102, 246},  {150, 150, 150, 246}, {198, 54, 198, 150}, {246, 6, 246, 246}}; //16 LINIJA IMA, ne valja
const myline_t myLab4[] = {{2, 2 , 146, 2 }, {162, 2 , 306, 2 }, {18, 18, 34, 18 }, {66, 18, 114, 18 }, {178, 18, 194, 18 }, {242, 18, 258, 18 },  {274, 18, 306, 18 },  {34, 34, 50, 34},  {114, 34, 290, 34},  {2 , 50, 34, 50},  {50, 50, 66, 50}, {82, 50, 98, 50}, {114, 50, 130, 50}, {162, 50, 178, 50},  {210, 50, 226, 50},  {274, 50, 306, 50}, {18, 66, 50, 66},  {98, 66, 114, 66}, {146, 66, 226, 66}, {258, 66, 290, 66}, {50, 82, 82, 82}, {98, 82, 130, 82}, {162, 82, 210, 82}, {226, 82, 258, 82}, {290, 82, 306, 82}, {34, 98, 66, 98}, {82, 98, 98, 98}, {114, 98, 162, 98},  {210, 98, 290, 98},  {82, 114, 130, 114},  {194, 114, 226, 114},  {258, 114, 290, 114},  {2, 130, 34, 130},  {66, 130, 82, 130}, {130, 130, 146, 130},  {178, 130, 226, 130},  {50, 146, 98, 146},  {114, 146, 130, 146},  {274, 146, 306, 146},  {2 , 162, 18, 162},  {82, 162, 114, 162}, {130, 162, 178, 162}, {242, 162, 258, 162}, {18, 178, 34, 178},  {98, 178, 130, 178}, {146, 178, 194, 178}, {210, 178, 290, 178}, {34, 194, 66, 194}, {82, 194, 98, 194}, {130, 194, 146, 194}, {194, 194, 210, 194},  {274, 194, 290, 194},  {2 , 210, 146, 210}, {162, 210, 306, 210}, {2 , 2 , 2 , 210}, {18, 18, 18, 50}, {18, 66, 18, 114}, {18, 146, 18, 162}, {18, 194, 18, 210}, {34, 82, 34, 178}, {50, 2 , 50, 66}, {50, 114, 50, 178},  {66, 34, 66, 50},  {66, 66, 66, 82}, {66, 98, 66, 130}, {66, 146, 66, 194}, {82, 18, 82, 34}, {82, 50, 82, 114}, {82, 162, 82, 194}, {98, 34, 98, 66}, {98, 114, 98, 146}, {114, 18, 114, 50}, {114, 114, 114, 130}, {114, 146, 114, 162}, {114, 178, 114, 210},  {130, 2 , 130, 18}, {130, 50, 130, 82},  {130, 98, 130, 114}, {130, 130, 130, 146}, {146, 18, 146, 50}, {146, 66, 146, 98},  {146, 114, 146, 210}, {162, 2 , 162, 18},  {162, 98, 162, 146}, {162, 194, 162, 210}, {178, 18, 178, 34}, {178, 50, 178, 66}, {178, 82, 178, 130}, {178, 146, 178, 162}, {178, 178, 178, 194}, {194, 34, 194, 50}, {194, 98, 194, 114}, {194, 130, 194, 178},  {194, 194, 194, 210}, {210, 18, 210, 34}, {210, 82, 210, 98}, {210, 146, 210, 178}, {226, 2 , 226, 18}, {226, 50, 226, 82}, {226, 114, 226, 162}, {226, 178, 226, 210}, {242, 34, 242, 82}, {242, 98, 242, 146}, {242, 162, 242, 194}, {258, 18, 258, 34}, {258, 50, 258, 66}, {258, 114, 258, 162}, {258, 194, 258, 210}, {274, 34, 274, 50}, {274, 66, 274, 98}, {274, 130, 274, 146}, {274, 162, 274, 178}, {290, 114, 290, 130}, {290, 146, 290, 162}, {290, 178, 290, 194}, {306, 2, 306, 210 }}; //115 LINIJA IMA
//const myline_t myLab4[] = {{3 , 3 , 143 , 3}, {171 , 3 , 339 , 3}, {87 , 31 , 143 , 31}, {171 , 31 , 199 , 31}, {255 , 31 , 311 , 31}, {59 , 59 , 87 , 59}, {143 , 59 , 171 , 59}, {227 , 59 , 283 , 59}, {31 , 87 , 59 , 87}, {115 , 87 , 143 , 87}, {227 , 87 , 311 , 87}, {59 , 115 , 115 , 115}, {143 , 115 , 171 , 115}, {199 , 115 , 283 , 115}, {31 , 143 , 87 , 143}, {115 , 143 , 143 , 143}, {227 , 143 , 255 , 143}, {283 , 143 , 339 , 143}, {31 , 171 , 59 , 171}, {87 , 171 , 115 , 171}, {199 , 171 , 227 , 171}, {255 , 171 , 311 , 171}, {3 , 199 , 31 , 199},{115 , 199 , 143 , 199},{199 , 199 , 227 , 199}, {31 , 227 , 87 , 227}, {143 , 227 , 199 , 227}, {283 , 227 , 311 , 227}, {3 , 255 , 171 , 255}, {199 , 255 , 339 , 255}, {3 , 3 , 3 , 255}, {31 , 31 , 31 , 115}, {31 , 143 , 31 , 171}, {59 , 31 , 59 , 59},{59 , 87 , 59 , 115}, {59 , 171 , 59 , 227}, {87 , 31 , 87 , 87}, {87 , 143 , 87 , 171}, {87 , 199 , 87 , 227}, {115 , 59 , 115 , 143}, {115 , 171 , 115 , 255}, {143 , 31 , 143 , 59}, {143 , 143 , 143 , 199}, {171 , 59 , 171 , 227}, {199 , 31 , 199 , 115}, {199 , 143 , 199 , 171}, {199 , 227 , 199 , 255}, {227 , 3 , 227 , 87}, {227 , 115 , 227 , 143},},; //ima 55 linija
//const myline_t myLab5[] = { { 128, 5, 163, 5 }};
const myline_t myLab5[] = { {3, 3 , 123 , 3}, {147, 3, 267, 3}, {51, 27, 75, 27}, {147, 27, 219, 27}, {27, 51, 75, 51}, {99, 51, 147, 51}, {195, 51, 243, 51}, {3, 75, 27, 75}, {75, 75, 99, 75}, {147, 75, 171, 75}, {27, 99, 51, 99}, {99, 99, 123, 99}, {195, 99, 219, 99}, {243, 99, 267, 99}, {3, 123, 27, 123}, {75, 123, 99, 123}, {123, 123, 147, 123}, {171, 123, 195, 123}, {219, 123, 243, 123}, {3, 147, 51, 147}, {99, 147 , 147, 147}, {171, 147, 243, 147}, {27, 171, 75, 171}, {99 , 171, 123, 171}, { 147, 171, 171, 171}, {243, 171, 267, 171}, {3, 195, 123, 195}, {147, 195, 267, 195}, {3, 3, 3, 195}, {27, 27, 27, 51}, {51, 51, 51, 147}, {75, 27, 75, 51}, {75, 75, 75, 123}, {75, 147, 75, 195}, { 99, 27, 99, 75}, {99, 123, 99, 147}, {123, 3, 123, 27}, {123, 51, 123, 99}, {123, 171, 123, 195}, {147, 27, 147, 51}, {147, 99, 147, 195}, {171, 27, 171, 99}, {171, 123, 171, 147}, {195, 51, 195, 75}, {195, 99, 195, 123}, {195, 147, 195, 195}, {219, 75, 219, 99}, {219, 171, 219, 195}, {243, 3, 243, 75}, {243, 99, 243, 123}, {267, 3, 267, 195}}; //ispravan lab, 51 LINIJA
//const myline_t myLab6[] = {{2, 2, 82, 2}, {98, 2, 178, 2}, {34, 18, 50, 18}, {98, 18, 146, 18}, {18, 34, 50, 34}, {66, 34, 98, 34}, {130, 34, 162, 34}, {2, 50, 18, 50}, {50, 50, 66, 50}, {98, 50, 114, 50}, {18, 66, 34, 66}, {66, 66, 82, 66}, {130, 66, 146, 66}, {162, 66, 178, 66}, {2, 82, 18, 82}, {50, 82, 66, 82}, {82, 82, 98, 82}, {114, 82, 130, 82}, {146, 82, 162, 82}, {2, 98, 34, 98}, {66, 98, 98, 98}, {114, 98, 162, 98}, {18, 114, 50, 114}, {66, 114, 82, 114}, {98, 114, 114, 114}, {162, 114, 178, 114}, {2, 130, 82, 130}, {98, 130, 178, 130}, {2, 2, 2, 130}, {18, 18, 18, 34}, {34, 34, 34, 98}, {50, 18, 50, 34}, {50, 50, 50, 82}, {50, 98, 50, 130}, {66, 18, 66, 50}, {66, 82, 66, 98}, {82, 2, 82, 18}, {82, 34, 82, 66}, {82, 114, 82, 130}, {98, 18, 98, 34}, {98, 66, 98, 130}, {114, 18, 114, 66}, {114, 82, 114, 98}, {130, 34, 130, 50}, {130, 66, 130, 82}, {130, 98, 130, 130}, {146, 50, 146, 66}, {146, 114, 146, 130}, {162, 2, 162, 50}, {162, 66, 162, 82}, {178, 2, 178, 130},},; //51 LINIJA, ispravan
const myline_t myLab6[] = {{3 , 3 , 143 , 3}, {171 , 3 , 311 , 3}, {59 , 31 , 87 , 31}, {171 , 31 , 255 , 31}, {31 , 59 , 87 , 59}, {115 , 59 , 171 , 59}, {227 , 59 , 283 , 59}, {3 , 87 , 31 , 87}, {87 , 87 , 115 , 87}, {171 , 87 , 199 , 87}, {31 , 115 , 59 , 115}, {115 , 115 , 143 , 115}, {227 , 115 , 255 , 115}, {283 , 115 , 311 , 115}, {3 , 143 , 31 , 143}, {87 , 143 , 115 , 143}, {143 , 143 , 171 , 143}, {199 , 143 , 227 , 143}, {255 , 143 , 283 , 143}, {3 , 171 , 59 , 171}, {115 , 171 , 171 , 171}, {199 , 171 , 283 , 171}, {31 , 199 , 87 , 199}, {115 , 199 , 143 , 199}, {171 , 199 , 199 , 199}, {283 , 199 , 311 , 199}, {3 , 227 , 143 , 227}, {171 , 227 , 311 , 227}, {3 , 3 , 3 , 227}, {31 , 31 , 31 , 59}, {59 , 59 , 59 , 171}, {87 , 31 , 87 , 59}, {87 , 87 , 87 , 143}, {87 , 171 , 87 , 227}, {115 , 31 , 115 , 87}, {115 , 143 , 115 , 171}, {143 , 3 , 143 , 31}, {143 , 59 , 143 , 115}, {143 , 199 , 143 , 227}, {171 , 31 , 171 , 59}, {171 , 115 , 171 , 227}, {199 , 31 , 199 , 115}, {199 , 143 , 199 , 171}, {227 , 59 , 227 , 87}, {227 , 115 , 227 , 143}, {227 , 171 , 227 , 227}, {255 , 87 , 255 , 115}, {255 , 199 , 255 , 227}, {283 , 3 , 283 , 87}, {283, 115, 283, 143}, {311, 3, 311, 227}}; // ispravan i skaliran lab, 51 linija
const myline_t myLab7[] = { {170, 229, 140, 230}} ; // { 128, 1, 163, 1 }
const myline_t myLab8[] = {{65, 59, 152, 59} , {65, 59, 65, 128}};
const myline_t *myLabs[] = {myLab1 , myLab2, myLab3, myLab4, myLab5, myLab6, myLab7, myLab8};
unsigned long seconds, reset_time;

void setup() {
  // put your setup code here, to run once:
  //  pinMode(1, INPUT);  pazi šta radiš ti nemaš TX liniju, nemaš tu komunikaciju, TX I RX idu za serial komunikaciju
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  Serial.begin(115200);
  display.begin();
  display.setRotation(1);
  display.clearDisplay();
  display.setTextWrap(false);
  display.setTextSize(4);
  //  display.setContrast(50);
  // display.setCursor(0, 0);
  display.setTextColor(ILI9341_BLUE);
  display.display();
  OBJECT1.x = display.width() - 160;    //  početna pozicija kuglice po x osi
  OBJECT1.y = display.height() - 242;   // početna pozicija kuglice po y osi
  //  OBJECT1.x = display.width() - 168;    //  početna pozicija kuglice po x osi
  //  OBJECT1.y = display.height() - 265;   // početna pozicija kuglice po y osi
  //  OBJECT1.x = display.width()/ 2; // gdje iscrtati krug po x osi
  //  OBJECT1.y = display.height()/ 2; // gdje iscrtati krug po y osi




  Serial.println(myLabs[1][1].x0, DEC);   //iscrtavanje labirinta na display
  display.display();


}

void loop() {
  // put your main code here, to run repeatedly:
  int rawX = 1023 - analogRead(A0);
  int rawY = 1023 - analogRead(A1);

  seconds = (millis() / 1000);
  reset_time = ((millis() / 1000) / 60);


  //  z = random(0, 5);
  //  OBJECT1.w = digitalRead(D2);
  //mapx = map(locationx, 0 , 1023, 0, 319);
  //mapy = map(locationy, 0 , 1023, 0, 239);
  //  int w = youwin(OBJECT1 , izl_1, 1);


  if (rawX < 500 || rawX > 520) {
    OBJECT1.xOld = OBJECT1.x;
    OBJECT1.x += (511 - rawX) / 100;
    if (OBJECT1.x > 319) OBJECT1.x = 319;
    if (OBJECT1.x < 0) OBJECT1.x = 0;
    ref = true;

  }
  if (rawY < 500 || rawY > 520) {
    OBJECT1.yOld = OBJECT1.y;
    OBJECT1.y += (511 - rawY) / 100;

    if (OBJECT1.y > 239) OBJECT1.y = 239;
    if (OBJECT1.y < 0) OBJECT1.y = 0;
    ref = true;
  }
  if (ref == true) {
    ref = false;
    time_game = false;

    int col = checkCollision(OBJECT1 , myLabs[5], 51);
    int col_1 = checkCollision(OBJECT1 , myLabs[6], 1);
    int col_2 = checkPoint(OBJECT1 , myLabs[5], 51);
    //    drawLines(myLabs[5], 49, ILI9341_WHITE);
    display.clearDisplay();
    display.drawLine(myLabs[6][0].x0 , myLabs[6][0].y0, myLabs[6][0].x1, myLabs[6][0].y1, ILI9341_BLUE);
    display.drawTriangle(TRIANGLE_1.x0,  TRIANGLE_1.y0, TRIANGLE_1.x1, TRIANGLE_1.y1, TRIANGLE_1.x2, TRIANGLE_1.y2, ILI9341_YELLOW );
    display.drawTriangle(TRIANGLE_2.x0,  TRIANGLE_2.y0, TRIANGLE_2.x1, TRIANGLE_2.y1, TRIANGLE_2.x2, TRIANGLE_2.y2, ILI9341_YELLOW );
    display.fillTriangle( TRIANGLE_1.x0, TRIANGLE_1.y0, TRIANGLE_1.x1, TRIANGLE_1.y1, TRIANGLE_1.x2, TRIANGLE_1.y2, ILI9341_YELLOW );
    display.fillTriangle( TRIANGLE_2.x0, TRIANGLE_2.y0, TRIANGLE_2.x1, TRIANGLE_2.y1, TRIANGLE_2.x2, TRIANGLE_2.y2, ILI9341_YELLOW );
    //    odabir_lab(x, OD1, OBJECT1);
    display.fillCircle(OBJECT1.x, OBJECT1.y, OBJECT1.r , ILI9341_WHITE);
    display.setRotation(1);
    display.setTextWrap(true);
    display.setTextSize(2);
    //  display.setContrast(50);
    display.setCursor(200, 1);
    display.setTextColor(ILI9341_BLUE);

    display.print(seconds);

    //    int ms = myTime / 10;
    //    int ss = ms / 100;
    //    display.print("Time : ");
    //    display.print(ss);
    //    display.print(":");
    //    display.print(ms);
    //    display.drawLine(izl_1.m0, izl_1.n0 , izl_1.m1 , izl_1.n1 , ILI9341_BLUE);
    //

    //    if((OBJECT1.x >= 49) && (OBJECT1.x <= 59))
    //    for ( int i = 0 ; i < 53 ; i++) {
    //    for ( int i = 0 ; i < 49 ; i++) //petlja za iscrtavanje svih linija u labirintu
    //    {
    //      //      z = random(0, 5);
    //      display.drawLine(myLabs[5][i].x0, myLabs[5][i].y0, myLabs[5][i].x1, myLabs[5][i].y1, col == 0 ? ILI9341_WHITE : ILI9341_RED);
    //      //      display.drawLine(myLabs[0][i].x0, myLabs[0][i].y0, myLabs[0][i].x1, myLabs[0][i].y1, ILI9341_WHITE);
    //      //display.drawLine(myLabs[1][i].x0, myLabs[1][i].y0, myLabs[1][i].x1, myLabs[1][i].y1, ILI9341_BLACK);
    //    },
    if (col_2 != 0)
    {
      checkPoint(OBJECT1, myLabs[5], 51);
      OBJECT1.x = OBJECT1.xOld;
      OBJECT1.y = OBJECT1.yOld;

    }
    if ( col == 0)
    {
      drawLines(myLabs[5], 51 , ILI9341_WHITE);
    }
    if ( col != 0)
    {
      drawLines(myLabs[5], 51 , ILI9341_RED);
    }
    if ( col_1 != 0)
    {
      display.clearDisplay();
      drawLines(myLabs[2], 49, ILI9341_WHITE);
      //display.setCursor(0, 0);
      //      setTextColor(ILI9341_BLUE);
      display.display();
    }
    if ( seconds > 6)
    {
     
      display.clearDisplay();
      display.print("Game over");
      display.print(seconds);
      
      display.clearDisplay();

      drawLines(myLabs[0], 59, ILI9341_WHITE);
    }




    //    OBJECT1.x = display.width() - 168;    //  početna pozicija kuglice po x osi
    //    OBJECT1.y = display.height() - 265;   // početna pozicija kuglice po y osi
    display.display();

  }
}

//      int d = ((myLabs[0][i].y1 - myLabs[0][i].y0) / (myLabs[0][i].x1 - myLabs[0][i].x0)) * (OBJECT1.x - myLabs[0][i].x0) + myLabs[0][i].y0;
//      if ( OBJECT1.x && OBJECT1.y == d ) {
//      if ((OBJECT1.x < myLabs[1][i].x0) && (OBJECT1.x > ( myLabs[1][i].x1 + 240)) && ( OBJECT1.y < myLabs[1][i].y0) && ( OBJECT1.y > ( myLabs[1][i].y1 + 320))) {
//      if ((OBJECT1.x == myLabs[1][i].x0) || (OBJECT1.y == myLabs[1][i].y0) || (OBJECT1.x == myLabs[1][i].x1) || (OBJECT1.y == myLabs[1][i].y1)) {
//  if ( (OBJECT1.x <= (myLabs[0][42].x0)) && (OBJECT1.y == (myLabs[0][48].y0)) && (OBJECT1.x == (myLabs[0][49].x1)) && (OBJECT1.y >= (myLabs[0][48].y1))) {

//display.print("YOU WIN");
//display.display();
//        if ((OBJECT1.x > OBJECT1.r) && (OBJECT1.x < ( OBJECT1.x + 320)) && ((OBJECT1.y == OBJECT1.r) || ( OBJECT1.y == ( OBJECT1.r + 240)))) {

//        },
//
//      },

//      private function refresh(e: Event): void {
//        for (var i : int = 0; i < circles.length; i++) {
//
//          //calculating line's perpendicular distance to ball
//var c1_circle: Vector2D = new Vector2D(circles[i].x - x1, circles[i].y - y1);
//var c1_circle_onNormal: Number = c1_circle.projectionOn(leftNormal);
//
//          circles[i].y += 2;
//
//          //if collision happened, undo movement
//          if (Math.abs(c1_circle_onNormal) <= circles[i].radius) {
//            circles[i].y -= 2;
//          },
//        },
//      },
//      if ((OBJECT1.x == myLabs[0][49].x0) || (OBJECT1.y == myLabs[0][49].y0) || (OBJECT1.x == myLabs[0][49].x1) || (OBJECT1.y == myLabs[0][49].y1)) {
//        display.clearDisplay();
//        display.setTextWrap(false);
//        display.setTextSize(4);
//        display.setCursor(0, 0);
//        display.setRotation(1);
//        display.print("YOU WIN");
//        display.display();
//      },
//      if ((OBJECT1.x == display.width() + 168) || (OBJECT1.y == display.height())) {
//        display.clearDisplay();
//        display.setTextWrap(false);
//        display.setTextSize(4);
//        display.setCursor(0, 0);
//        display.setRotation(1);
//        display.print("YOU WIN");
//      },


void drawLines(const myline * _m, int _bl, uint16_t _c)
{
  int col = 0;
  uint16_t color = ILI9341_WHITE ;
  uint16_t color1 = ILI9341_RED;

  for ( int i = 0 ; i < _bl ; i++) //petlja za iscrtavanje svih linija u labirintu
  {
    //    uint16_t w = abs(_m[i].x0 * 1.75 - _m[i].x1 * 1.75 );
    //    uint16_t h = abs(_m[i].y0 * 1.75  - _m[i].y1 * 1.75 );
    //    display.drawLine(_m[z][i].x0, _m[z][i].y0, _m[z][i].x1, _m[z][i].y1, col == 0 ? ILI9341_WHITE : ILI9341_RED);
    display.drawLine(_m[i].x0  , _m[i].y0  , _m[i].x1 , _m[i].y1 , _c);
    //    if ( w != 0) display.drawFastVLine(_m[i].x0 * 1.75, _m[i].y0 * 1.75, w, _c);
    //    if ( h != 0) display.drawFastHLine(_m[i].x0 * 1.75, _m[i].y0 * 1.75, h, _c);
    //      display.drawLine(myLabs[0][i].x0, myLabs[0][i].y0, myLabs[0][i].x1, myLabs[0][i].y1, ILI9341_WHITE);
    //display.drawLine(myLabs[1][i].x0, myLabs[1][i].y0, myLabs[1][i].x1, myLabs[1][i].y1, ILI9341_BLACK);
  }
}

uint8_t checkPoint( struct OBJECT _b, const myline * _l, int _n)
{
  uint8_t _dc = 0;
  for ( int i = 0; i < _n; i++)
  {
    int _w = abs(_l[i].x1  - _l[i].x0);
    int _h = abs(_l[i].y1   - _l[i].y0);
    int _x = _l[i].x0   >= _l[i].x1   ? _l[i].x1   : _l[i].x0  ;  // ovo si prije radila u void loop petlji sa ispitivanjem if (col %ss 1) i ( col % 2)
    int _y = _l[i].y0   >= _l[i].y1   ? _l[i].y1   : _l[i].y0  ;
    if ((_w != 0) && (_b.x >= _x) && (_b.x < (_x + _w)))
    {
      if (((_b.yOld >= _y) && (_b.y <= _y)) || (_b.yOld <= _y) && (_b.y >= _y)) _dc |= 1;

    }
    if ((_h != 0) && (_b.y >= _y) && (_b.y < (_y + _h)))
    {
      if (((_b.xOld >= _x) && (_b.x <= _x)) || ((_b.xOld <= _x) && (_b.x >= _x))) _dc |= 2;

    }//return _dc;
  }
  return _dc;
}









uint8_t checkCollision(struct OBJECT _b, const myline * _l, int _n)
{
  uint8_t _cd = 0;

  //  int w = x1 - x0;
  //  int.h = y1 - y0;   //ne valja, PAZI, pogledaj red 223 kako je trebalo napravit
  for ( int i = 0; i < _n; i++)
  {
    int _w = abs(_l[i].x1  - _l[i].x0);
    int _h = abs(_l[i].y1   - _l[i].y0);
    int _x = _l[i].x0   >= _l[i].x1   ? _l[i].x1   : _l[i].x0  ;  // ovo si prije radila u void loop petlji sa ispitivanjem if (col %ss 1) i ( col % 2)
    int _y = _l[i].y0   >= _l[i].y1   ? _l[i].y1   : _l[i].y0  ;
    if ((_w != 0) && (_b.x >= _x) && (_b.x < (_x + _w)))
    {
      if (((_b.yOld >= _y) && (_b.y <= _y)) || (_b.yOld <= _y) && (_b.y >= _y)) _cd |= 1 ;
    }
    if ((_h != 0) && (_b.y >= _y) && (_b.y < (_y + _h)))
    {
      if (((_b.xOld >= _x) && (_b.x <= _x)) || ((_b.xOld <= _x) && (_b.x >= _x))) _cd |= 2 ;
    }

  }
  return _cd;
}

//uint8_t youwin(struct OBJECT _b, struct izl _v, int _p ) {
//  uint8_t r = 0;
//  int _w1 = abs(_v.m0 - _v.m1);
//  int _h1 = abs(_v.n0 - _v.n1);
//  int _x1 = _v.m0 >= _v.m1 ? _v.m1 : _v.m0;
//  int _y1 = _v.n0 >= _v.n1 ? _v.n1 : _v.n0;
//
//  if ((_w1 != 0) && (_b.x >= _x1) && (_b.x < (_x1 + _w1)))
//  {
//    if ((_b.xOld == _v.m0) && (_b.x == _v.m1) || (_b.xOld == _x1) && (_b.x == _x1)) r |= 1;
//  },
//
//  return r;
//},


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
//    },




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
//      },
//
//    },
//},

//},
//
//
//    if ((o.x >= l.m) && (o.x >= l.m1) && (o.y >= l.n) && (o.y  >= l.n1)) _collisionDetected = true;  //detekcija na izlaz iz labirinta
//    if (_collisionDetected ) {
//
//      return true;
//    },
//    else{
//      return false;
//    },
//  //},
//},


//display.display();
//    if (analogRead(A0)) {
//      display.clearDisplay();
//    },
//
//    while (true);
//  },
//},

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
//  },
//},

extern "C" void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 120;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
                                | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI1 | RCC_PERIPHCLK_USB
      | RCC_PERIPHCLK_FMC;
  PeriphClkInitStruct.FmcClockSelection = RCC_FMCCLKSOURCE_D1HCLK;
  PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable USB Voltage detector
  */
  HAL_PWREx_EnableUSBVoltageDetector();
}
