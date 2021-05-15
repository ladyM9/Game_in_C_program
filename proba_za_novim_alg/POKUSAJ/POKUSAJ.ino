#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
int rectw = 40; //duljina stranice kv
int recth = 40;//visina stranice kv
int rectlocx = 0; //lokacija po x osi od kvadrata
int rectlocy = 0; //

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


const myline_t myLab1[] = {{7, 22, 7, 37},{1, 8, 7, 8}};
const myline_t myLab2[] = {{27, 16, 36, 8} , {52, 43, 29, 12}};
const myline_t *myLabs[] = {myLab1 , myLab2};
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

  Serial.println(myLabs[1][1].x0, DEC);
  display.drawRect(0, 0 , 84 , 48, BLACK);

  for ( int i = 0 ; i < 2; i++)
  {
    display.drawLine(myLabs[0][i].x1, myLabs[0][i].y1, myLabs[0][i].x0, myLabs[0][i].y0, BLACK);

  }
  display.display();


}

void loop() {
  // put your main code here, to run repeatedly:

}
