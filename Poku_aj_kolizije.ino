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
int rectw = 20;
int recth = 20;
int rectlocx = 0; //weith od kvadrata
int rectlocy = 0; //
bool collision = false;
char CollisionDect(int rectlocx, int rectlocy, int recth, int rectw, int locationx, int locationy, int x, int y);
char rect;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  display.begin();
  locationx = display.width() / 2;
  locationy = display.height() / 2;
  rectlocx = (display.width() / 2) - (rectw / 2); // gdje iscrtati kvadrat po x osi
  rectlocy = (display.height() / 2) - (recth / 2); // gdje iscrtati kvadrat po y osi
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

  x = 1023 - analogRead(A0);
  y = 1023 - analogRead(A1);
  w = digitalRead(D2);
  mapx = map(locationx, 0 , 1023, 0, 83);
  mapy = map(locationy, 0 , 1023, 0, 47);

  if (x < 500 || x > 520) {
    locationx += (511 - x) / 50;
    if (locationx > 83) locationx = 83;
    if (locationx < 0) locationx = 0;
    ref = true;

  }
  if (y < 500 || y > 520) {
    locationy += (511 - y) / 50;
    if (locationy > 47) locationy = 47;
    if (locationy < 0) locationy = 0;
    ref = true;
  }

  if (ref) {
    ref = false;
    display.clearDisplay();
    //    display.drawLine(0, 15, 100, 25, BLACK);
    //    display.drawLine(20, 5, 100, 10, BLACK);
    display.fillCircle(locationx, locationy, 2 , BLACK);
    display.drawRect(rectlocx, rectlocy , rectw , recth, BLACK);
    display.display();
    rect = CollisionDect(rectlocx, rectlocy, recth, rectw, locationx,locationy, x, y);
    delay(100);

  }
}
char CollisionDect(int rectlocx, int rectlocy, int recth, int rectw, int locationx, int locationy, int x, int y) {
  char rect;
  if ((rectlocy > 83 ) || (rectlocy > 47)) {
    collision = true;
    rect = "Game over" ;
    display.print("Game over") ; 
  }
}return rect;



  //  if(digitalRead(USER_BTN) == true) {
  //    display.print("Tipka pritisnuta");
  //  }
  //  else {
  //    display.print("Tipka nije pritisnuta");
  //
  //  display.print(digitalRead(USER_BTN) ? "Tipka pritisnuta" : "Tipka nepritisnuta"); // pomocu kondicionala, dakle ako je USER_BTN true ispiši tipka pritisnuta, inace tipka nepritisnuta
