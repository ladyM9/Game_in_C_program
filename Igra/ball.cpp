#include "ball.h"
#include "screen.h"
#include "maze.h"
#include "lab.h"
#include "SparkFunLSM6DSO.h"

Ball::Ball(void (*_callBack)())
{

  requestForCallback = _callBack;
}
void Ball::firstBallposition(Adafruit_ILI9341 &lcd, myMaze_t *_currentLab) // metoda za iscrtavanje kuglice na pocetnoj poziciji u svakom pojedinom labirintu( za svaki labirint je drugacije)
{
  xCurrent = _currentLab->startPosX; // pocetna pozicija kuglice tj objekta na X osi
  yCurrent = _currentLab->startPosY + offset_y;
  Y = yCurrent;
  X = xCurrent;
  _color = ILI9341_BLUE;
  R = 2.5; // polumjer kuglice tj objekta
  lcd.fillCircle(xCurrent, yCurrent + offset_y, R, _color);
}
void Ball::updateScreen()
{
  requestForCallback();
}

void Ball::updateBallposition(Adafruit_ILI9341 &lcd, LSM6DSO myIMU)
{
  //varijable za akceleraciju kuglice
  float rawX =  myIMU.readFloatAccelX();
  float rawY =  myIMU.readFloatAccelY();

  //Serial.printf("Raw x: %d, Raw y: %d\r\n", rawX, rawY);
  //int rawX = 1023 - analogRead(A1); // citanje analogne vrijednosti trenutno sa joysticka
  //int rawY = 1023 - analogRead(A0);
  velX += rawX;
  velY += rawY;
  //xCurrent = X;
  //yCurrent = Y;
  if(velX > 0.5) velX = 0.5;
  if(velY > 0.5) velY = 0.5;
  if (velX < -0.5) velX = -0.5;
  if (velY < -0.5) velY = -0.5;

  xCurrent += velX;
  yCurrent += velY;
  Serial.printf("X: %.2f, Y: %.2f , velX: %.2f, velY: %.2f\r\n", xCurrent,yCurrent,velX, velY);
  

  lcd.fillCircle(xCurrent, yCurrent, R, _color); // ispisivanje kuglice na poetnoj poziciji, tu mora pisat ovo( NEPREMJEĹ TAJ INAÄ†E SE NEÄ†E ISPISAT NA DISPLAY)
  updateScreen();                  // pozivanje funkcije za update screena koja nam omogucava da kad mi pomocu joysticka pomicemo kuglicu da tu kuglicu iscrtava na jednoj pozicije a brise na prosloj poziciji
}

uint8_t Ball::checkColision(myMaze_t *_currentLab) // metoda koja radi provjeru da li se dogodila kolizija izmedu kuglice i linije u pojedinom labirintu, *_currentlab je pokazivac na lab
{
  score = false;                                       // zastavica score je u prvom trenutku false jer kad uđemo u labirint kolizija se još nije dogodila
  myline_t *m = _currentLab->labLines;                 //*m je pokazivac u kojem je pohranjen pojedini labirint i dohvaca linije u tom labirintu
  uint8_t _cd = 0;                                     // zastavica pomocu koje provjeravamo da li se dogodila kolizija ili nije
  for (int i = 0; i < _currentLab->numberOfLines; i++) // kreni od nulte linije u labirintu i idi do zadnje linije
  {
    int _w = abs(m[i].x1 - m[i].x0);                           // izracunaj duljinu pojedine linije po x osi
    int _h = abs((m[i].y1 + offset_y) - (m[i].y0 + offset_y)); // izracunaj visinu linije po y osi
    int _x = m[i].x0 >= m[i].x1 ? m[i].x1 : m[i].x0;           // ovo si prije radila u void loop petlji sa ispitivanjem if (col %ss 1) i ( col % 2)
    int _y = (m[i].y0 + offset_y) >= (m[i].y1 + offset_y) ? (m[i].y1 + offset_y) : (m[i].y0 + offset_y);

    if ((_w != 0) && (X >= _x) && (X < (_x + _w))) // ispitivanje da li se dogodila kolizija na x osi
    {
      if (((yCurrent >= _y) && (Y <= _y)) || (yCurrent <= _y) && (Y >= _y))
      {
        _cd |= 1;
        score = true; // ako se dogodila kolizija po x osi zastavicu score stavi na true
      }
    }

    if ((_h != 0) && (Y >= _y) && (Y < (_y + _h))) // ispitivanje da li se dogodila kolizija na y osi
    {
      if (((xCurrent >= _x) && (X <= _x)) || ((xCurrent <= _x) && (X >= _x)))
      {
        _cd |= 2;
        score = true;
      }
    }
    if (X <= 0)
      _cd |= 1;
    if (Y <= 0)
      _cd |= 2;
    if (Y <= 20)
      _cd |= 2;
    if ((Y <= 20) && (X >= 319))
      _cd |= 1;
  }

  return _cd; // vrati vrijednost odnosno gdje se dogodila kolizija
}

uint8_t Ball::checkExit(myMaze_t *_currentLab) // metoda pomocu koje se provjerava da li je kuglica dotaknila izlaznu liniju
{
  e = (_currentLab->endLine);
  uint8_t _el = false;                             // zastavica pomocu koje ispitujemo da li se dogodila kolizija na izlaznoj liniji u prvom trenutku je false
  int _w = abs(e.x1 - e.x0);                       // izracunavanje duljine izlazne linije
  int _h = abs(e.y1 + offset_y - e.y0 + offset_y); // izracunavanje visine izlazne linije
  int _x = e.x0 >= e.x1 ? e.x1 : e.x0;             // ovo si prije radila u void loop petlji sa ispitivanjem if (col %ss 1) i ( col % 2)
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
  X = xCurrent; // nova pozicija kuglice po x osi ako je kuglica dotaknila liniju, kuglicu vrati na proslu poziciju po x osi
  Y = yCurrent; // //nova pozicija kuglice po y osi ako je kuglica dotaknila liniju, kuglicu vrati na proslu poziciju po y osi
}
void Ball::exitLine(Adafruit_ILI9341 &lcd, myMaze_t *_currentLab) // metoda pomocu koje iscrtavam izlaznu liniju u pojedinom labirintu na display
{
  e = _currentLab->endLine; // udi u podatak u pojedinom labirintu i dohvati poziciju izlazne linije iz tog labirinta

  lcd.drawLine(e.x0, e.y0 + offset_y, e.x1, e.y1 + offset_y, ILI9341_MAGENTA); // ovako ako ne napises labirint ti se neÄ‡e prikazati na zaslonu!!!!!
}

void Ball::Time(Adafruit_ILI9341 &lcd, unsigned long A) // metoda pomocu koje ispisujem vrijeme u igrici na zaslon
{

  lcd.setCursor(15, 3);                   // kursor pomocu kojega postavljam na kojoj ce se poziciji ispisati vrijeme u igrici na zaslon
  lcd.setTextColor(ILI9341_GREEN);        // postavalje boje texta vremena u igrici
  lcd.setTextSize(2);                     // velicina teksta
  lcd.printf("%2ld", (unsigned long)(A)); // formatirani ispis vremena igrice na zaslon
}

void Ball::Score(Adafruit_ILI9341 &lcd) // metoda koja ispisuje score odnosno bodove u igrici na display tijekom igre
{
  uint8_t gameover = false;
  lcd.setCursor(200, 3);
  lcd.setTextSize(2);
  lcd.setTextColor(ILI9341_NAVY);
  if (score == true && scoreOld == false) // ako se dogodila kolizija i ako je scoreOld == false
  {
    bodovi += 1; // bodove u igrici smanji za 1
  }
  lcd.printf("%2ld", live); // ispisi score na display
  scoreOld = score;         // scoreOldu pridruzi novi score igrice
}

void Ball::score_Game(Adafruit_ILI9341 &lcd)
{

  lcd.setCursor(200, 20);
  lcd.setTextSize(2);
  lcd.setTextColor(ILI9341_NAVY);
  lcd.printf(" \n Score: %2ld \n", bodovi);
  lcd.println("\n");
  lcd.printf("\n Live: %2ld \n", live);
  ukupni_Bodovi(lcd);

  updateScreen();
}

void Ball::ukupni_Bodovi(Adafruit_ILI9341 &lcd)
{

  if ((bodovi >= 0) && (bodovi <= 10))

  {
    bodovi_igra += 100;
  }

  lcd.setCursor(200, 45);
  lcd.setTextSize(2);
  lcd.setTextColor(ILI9341_NAVY);
  lcd.printf("\n Score in game: %2ld", bodovi_igra);
}
