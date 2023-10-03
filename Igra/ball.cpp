#include "SparkFunLSM6DS3.h"
#include "ball.h"
#include "screen.h"
#include "maze.h"
#include "lab.h"
#include "icons.h"
#include "Adafruit_GFX.h"
#include "ILI9341_STM32.h"

Ball::Ball(void (*_callBack)())
{

  requestForCallback = _callBack;
}
void Ball::firstBallposition(Adafruit_ILI9341 &lcd, myMaze_t *_currentLab) // metoda za iscrtavanje kuglice na pocetnoj poziciji u svakom pojedinom labirintu( za svaki labirint je drugacije)
{
  lcd.setRotation(3);
  xCurrent = _currentLab->startPosX;            // pocetna pozicija kuglice tj objekta na X osi
  yCurrent = _currentLab->startPosY + offset_y; // pocetna pozicija kuglice tj objekta na Y osi

  _color = ILI9341_BLUE;
  R = 2.5; // polumjer kuglice tj objekta
  lcd.fillCircle(xCurrent, yCurrent + offset_y, R, _color);
}
void Ball::updateScreen()
{
  requestForCallback();
}

void Ball::updateBallposition(Adafruit_ILI9341 &lcd, LSM6DS3 myIMU)
{
  // varijable za akceleraciju kuglice
  lcd.setRotation(3);
  float rawX = myIMU.readFloatAccelX(); // citanje vrijednosti pozicije akcelerometra po x osi
  float rawY = myIMU.readFloatAccelY(); // citanje pozicije akcelerometra po y osi


  velX = rawX * -5;
  velY = rawY * -5;

  X = xCurrent; // X je nova pozicija kuglice, novoj poziciji kuglice po x osi pridruzi staru poziciju
  Y = yCurrent;

  xCurrent += velX; // pokretanje kuglice pomocu akcelerometra po x osi
  yCurrent += velY; // pokretanje kuglice pomocu akcelerometra po y osi

  lcd.fillCircle(xCurrent, yCurrent, R, _color); // ispisivanje kuglice na poetnoj poziciji, tu mora pisat ovo( NEPREMJEĹ TAJ INAÄ†E SE NEÄ†E ISPISAT NA DISPLAY)
  updateScreen();                                // pozivanje funkcije za update screena koja nam omogucava da kad mi pomocu joysticka pomicemo kuglicu da tu kuglicu iscrtava na jednoj pozicije a brise na prosloj poziciji
}

uint8_t Ball::checkColision(Adafruit_ILI9341 &lcd, myMaze_t *_currentLab) // metoda koja radi provjeru da li se dogodila kolizija izmedu kuglice i linije u pojedinom labirintu, *_currentlab je pokazivac na lab
{
  lcd.setRotation(3);
  score = false;                       // zastavica score je u prvom trenutku false jer kad uđemo u labirint kolizija se još nije dogodila
  myline_t *m = _currentLab->labLines; //*m je pokazivac u kojem je pohranjen pojedini labirint i dohvaca linije u tom labirintu
  uint8_t _cd = 0;                     // zastavica pomocu koje provjeravamo da li se dogodila kolizija ili nije, u prvom trenutku je 0 jer nema kolizije

  for (int i = 0; i < _currentLab->numberOfLines; i++) // kreni od nulte linije u labirintu i idi do zadnje linije
  {
    int _w = abs(m[i].x1 - m[i].x0);                           // izracunaj duljinu pojedine linije po x osi
    int _h = abs((m[i].y1 + offset_y) - (m[i].y0 + offset_y)); // izracunaj visinu linije po y osi
    int _x = m[i].x0 >= m[i].x1 ? m[i].x1 : m[i].x0;
    int _y = (m[i].y0 + offset_y) >= (m[i].y1 + offset_y) ? (m[i].y1 + offset_y) : (m[i].y0 + offset_y);

    if ((_w != 0) && (xCurrent >= _x) && (xCurrent < (_x + _w))) // ispitivanje da li se dogodila kolizija na x osi
    {
      if (((Y >= _y) && (yCurrent <= _y)) || (Y <= _y) && (yCurrent >= _y))
      {
        _cd |= 1;
        score = true; // ako se dogodila kolizija po x osi zastavicu score stavi na true
      }
    }

    if ((_h != 0) && (yCurrent >= _y) && (yCurrent < (_y + _h))) // ispitivanje da li se dogodila kolizija na y osi
    {
      if (((X >= _x) && (xCurrent <= _x)) || ((X <= _x) && (xCurrent >= _x)))
      {
        _cd |= 2;
        score = true;
      }
    }
    if (xCurrent <= 0) // ako je kuglica po x osi na 0 odnosno na rubu ekrana
      _cd |= 1;        // dogodila se kolizija
    if (yCurrent <= 0)
      _cd |= 2;
    if (yCurrent <= 20)
      _cd |= 2;

    if ((yCurrent <= 20) && (xCurrent >= 319)) // ako je kuglica na poziciji 20 po y osi i 319 po x osi kuglica je na gornjem rubu ekrana
      _cd |= 1;                                // dogodila se kolizija
  }

  return _cd; // vrati vrijednost odnosno gdje se dogodila kolizija
}

uint8_t Ball::checkExit(Adafruit_ILI9341 &lcd, myMaze_t *_currentLab) // metoda pomocu koje se provjerava da li je kuglica dotaknila izlaznu liniju
{
  lcd.setRotation(3);
  e = (_currentLab->endLine);                      // varijabla u koju je spremljena pozicija exit linije u labirintu
  uint8_t _el = false;                             // zastavica pomocu koje ispitujemo da li se dogodila kolizija na izlaznoj liniji u prvom trenutku je false
  int _w = abs(e.x1 - e.x0);                       // izracunavanje duljine izlazne linije
  int _h = abs(e.y1 + offset_y - e.y0 + offset_y); // izracunavanje visine izlazne linije
  int _x = e.x0 >= e.x1 ? e.x1 : e.x0;
  int _y = e.y0 + offset_y >= e.y1 + offset_y ? e.y1 + offset_y : e.y0 + offset_y;
  if ((_w != 0) && (X >= _x) && (X < (_x + _w))) // ispitivanje da li se dogodila kolizija izmedu kuglice i izlazne linije na x osi odnosno na sirini izlazne linije
  {
    if (((yCurrent >= _y) && (Y <= _y)) || (yCurrent <= _y) && (Y >= _y)) // ispitivanje da li se dogodila kolizija izmedu kuglice po y osi i izlazne linije odnosno njene visine
    {
      _el |= true; // ako se dogodila kolizija vrati true sto znaci da se dogodila kolizija
    }
    else
    {
      _el |= false; // inace vrati false
    }
  }
  return _el; // vrati da li je true ili false
}

void Ball::newBallposition(Adafruit_ILI9341 &lcd) // pomocu ove metode kad se dogodi kolizija kuglice i linije kuglica ce se vratiti na staru poziciju prije nego sto je dotaknila liniju
{
  lcd.setRotation(3);
  xCurrent = X; // nova pozicija kuglice po x osi ako je kuglica dotaknila liniju, kuglicu vrati na proslu poziciju po x osi
  yCurrent = Y; // //nova pozicija kuglice po y osi ako je kuglica dotaknila liniju, kuglicu vrati na proslu poziciju po y osi
}
void Ball::exitLine(Adafruit_ILI9341 &lcd, myMaze_t *_currentLab) // metoda pomocu koje iscrtavam izlaznu liniju u pojedinom labirintu na display
{
  lcd.setRotation(3);
  e = _currentLab->endLine; // udi u podatak u pojedinom labirintu i dohvati poziciju izlazne linije iz tog labirinta
                            // if(_currentLab->numberOfLines < 70)

  lcd.drawLine(e.x0, e.y0 + offset_y, e.x1, e.y1 + offset_y, ILI9341_MAGENTA); // iscrtavanje izlazne linije na display
}

void Ball::Time(Adafruit_ILI9341 &lcd, unsigned long time_game) // metoda pomocu koje ispisujem vrijeme u igrici na zaslon
{

  lcd.setCursor(15, 3);                           // kursor pomocu kojega postavljam na kojoj ce se poziciji ispisati vrijeme u igrici na zaslon
  lcd.setTextColor(ILI9341_GREEN);                // postavalje boje texta vremena u igrici
  lcd.setTextSize(2);                             // velicina teksta
  lcd.printf("%2ld", (unsigned long)(time_game)); // formatirani ispis vremena igrice na zaslon
}

uint8_t Ball::Score(Adafruit_ILI9341 &lcd) // metoda koja ispisuje score odnosno bodove u igrici na display tijekom igre
{
  uint8_t gameover = false;
  lcd.setCursor(60, 3);
  lcd.setTextSize(2);
  lcd.setTextColor(ILI9341_WHITE);
  lcd.printf("Live:%2ld",live); // ispisi zivote igraca na display
  lcd.setCursor(160, 3);
  lcd.setTextSize(2);
  lcd.setTextColor(ILI9341_WHITE);
  if (score == true && scoreOld == false) // ako se dogodila kolizija i ako je scoreOld == false
  {
    bodovi -= 1; // bodove u igrici smanji za 1
  }
  lcd.printf("Score:%2ld",bodovi); // ispisi zivote igraca na display

  
 
  scoreOld = score;         // scoreOldu pridruzi novi score igrice
  return bodovi;
}

uint8_t Ball::GM_SCORE(Adafruit_ILI9341 &lcd)
{
  uint8_t score0 = 0; //zastavica score0 je jednaka false tj 0
  if(bodovi == 0) //ako je igrac izgubio sve bodove odnosno ako su mu bodovi jednaki 0
  {
  score0 = 1; //zastavicu postavi na 1 odnosno na true
  bodovi = 50;  //bodove stavi na pocetni broj bodova sto je 50
  }
  return score0; //vrati zastavicu
  score0 = 0; //ponisti zastavicu
}

void Ball::score_Game(Adafruit_ILI9341 &lcd) // metoda pomocu koje na display se ispisuje broj bodova u igrici i zivoti u igrici
{

  lcd.setCursor(200, 20);
  lcd.setTextSize(2);
  lcd.setTextColor(ILI9341_NAVY);
  lcd.printf(" \n Score: %2ld \n", bodovi); // ispisivanje bodova u igrici koje je skupio korisnik
  lcd.println("\n");
  lcd.printf("\n Live: %2ld \n", live); // ispisivanje zivota korisnika
  ukupni_Bodovi(lcd);                   // pozivanje funkcije koja prati bodove korisnika u igrici odnosno racuna koliko je korisnik skupio bodova tijekom igre

  updateScreen();
}

void Ball::ukupni_Bodovi(Adafruit_ILI9341 &lcd)  //bodovi koje je korisnik uspio skupiti tijekom igranja igre
{

  lcd.setCursor(200, 45);
  lcd.setTextSize(2);
  lcd.setTextColor(ILI9341_NAVY);
  lcd.printf("\n Score in game: %2ld", bodovi_igra);
}

void Ball::win_Screen(Adafruit_ILI9341 &lcd) // metoda odnosno screen koji se ispisuje nakon sto je korisnik uspjesno prosao
// sve labirinte u pojedinom modu igre
{
  lcd.setCursor(100, 80);
  lcd.setTextSize(3);
  lcd.setTextColor(ILI9341_MAGENTA);
  lcd.print("YOU WIN!");

  updateScreen();
}

void Ball::game_Over(Adafruit_ILI9341 &lcd)  //metoda pomoću koje se opisuje tekst koji se prikazuje na zaslonu nakon sto dode do game over-a
{
  lcd.setCursor(100, 80);
  lcd.setTextSize(3);
  lcd.setTextColor(ILI9341_CYAN);
  lcd.print("GAME OVER!");
  updateScreen();
}

int Ball::Live(Adafruit_ILI9341 &lcd) //metoda unutar koje se oduzme zivot
{
  
  live = live - 1; //trenutnom broju zivota oduzmi jedan

  return live; //vrati novo stanje zivota
  //live+=1;
}

int Ball::no_l(Adafruit_ILI9341 &lcd) //metoda unutar koje se ispituje da li je igrac ostao bez zivota
{
  int a = 0; //zastavica je prvo postavljena na 0 odnosno false
  if(live == 0)  //ako je broj zivota jednak 0
  {
    a = 1; // a je 1 odnosno istina
    live = 3; //vrati broj zivota na 3
  }
  return a; //vrati a
  a = 0; //a vrati na 0 tj false tj ponisti zastavicu
}

void Ball::Bodovi_igra()
{
  if(bodovi == 5) //ako su bodovi na izlaznoj liniji jednaki 5
  {
  bodovi_igra+=10; //ukupnim bodovima u igri dodaj 10 bodova
  }
}

void Ball::picture(Adafruit_ILI9341 &lcd)
{
  lcd.setRotation(3);
  lcd.drawRGBBitmap(0,0,  image_data_Redmazescale, 186,100);
  lcd.drawRGBBitmap(120,120, image_data_Ponggamepicturescale, 180,120);
  lcd.setCursor(190, 20);
  lcd.setTextSize(3);
  lcd.setTextColor(ILI9341_BLUE);
  lcd.print("MAZE");
  lcd.setCursor(30, 190);
  lcd.setTextSize(3);
  lcd.setTextColor(ILI9341_GREEN);
  lcd.print("PONG");
  updateScreen();
}

void Ball::bod(Adafruit_ILI9341 &lcd, int draw, int Xb, int Yb)
{
  if (draw)
  {
    lcd.setRotation(3);
    lcd.drawRGBBitmap(Xb, Yb, image_data_Jagoda, 18, 18);
    // lcd.drawBitmap(10, 30 , epd_bitmap_Jagoda_za_igricu, 19 ,20, ILI9341_WHITE);
    updateScreen();
  }
}

int Ball::collision_bod(int xc, int yc)
{
  int col = 0;
  // if ((xp > x) && (xp < (w + x)) && (yp > y) && (yp < (h + y))
  int wb = 18 + Xb;
  int hb = 18 + Yb;

  // if ((xp > x) && (xp < (w + x)) && (yp > y) && (yp < (h + y))
  /*
  if ((X > Xb) && (X < (18 + Xb)) && (Y > Yb) && (Y < (18 + Yb)))
  {
    col = 1;
  }
  if (col == 1)
  {
    Serial.print("Collision");
  }
  */

  return col;
}