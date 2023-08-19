#include "Adafruit_GFX.h"
#include "ILI9341_STM32.h"
#include "SparkFunLSM6DS3.h"
#include "paddle.h"
#include "screen.h"

Pong::Pong(void (*_callBack)())
{
    _colorpaddle = ILI9341_RED;
    ballX = 160;
    ballY = 120;
    rb = 3;
    requestForCallback = _callBack;
}

void Pong::paddle1(Adafruit_ILI9341 &lcd, myPaddle_t1 *p1)
{

    yPOMAK1 = p1->sy1;
    xPOMAK1 = p1->sx1;

    wp = p1->w;
    hp = p1->h;

    lcd.fillRect(xPOMAK1, yPOMAK1, wp, hp, _colorpaddle); // paddle korisnik

    updateScreenGame1();
}

void Pong::paddle2(Adafruit_ILI9341 &lcd, myPaddle_t2 *p2)
{
    yPOMAK2 = p2->sy2;
    xPOMAK2 = p2->sx2;
    wp = p2->w;
    hp = p2->h;

    lcd.fillRect(xPOMAK2, yPOMAK2, wp, hp, _colorpaddle); // paddle računalo
    updateScreenGame1();
}

void Pong::movePaddle1(Adafruit_ILI9341 &lcd, LSM6DS3 myIMU)
{

    float rawX = myIMU.readFloatAccelX();
    float rawY = myIMU.readFloatAccelY();

    brzinax += rawX;
    brzinay += rawY;

    if (brzinax > 2)
        brzinax = 2;
    if (brzinay > 2)
        brzinay = 2;
    if (brzinax < -2)
        brzinax = -2;
    if (brzinay < -2)
        brzinay = -2;

    Y0 = yPOMAK1;

    /// kretanje prvog paddle, odnosno sa ovim paddle upravlja korisnik
    if (Y0 <= 0)
    {
        brzinay += 2;
    }

    if (Y0 >= 215)
    {
        brzinay -= 2;
    }
    // xPOMAK1 += brzinax;
    yPOMAK1 += brzinay;

    lcd.fillRect(xPOMAK1, yPOMAK1, wp, hp, _colorpaddle);

    updateScreenGame1();
}

void Pong::movePaddle2(Adafruit_ILI9341 &lcd)
{

    brzina2x += 2;
    brzina2y += 2;

    // kretanje drugog paddle odnosno sa ovim paddle upravlja računalo
  //  Y1 = yPOMAK2;

    if (yPOMAK2 >= 215)
    {
        brzina2y -= 1;
    }
    if (yPOMAK2 <= 0)
    {
        brzina2y += 1;
    }

    yPOMAK2 += ballY;
    
    
    lcd.fillRect(xPOMAK2, yPOMAK2, wp, hp, _colorpaddle);

    updateScreenGame1();
}

void Pong::movepaddleup(Adafruit_ILI9341 &lcd)
{
    /// yPOMAK2 -= 1;
    yPOMAK2 = Y1 - brzina2y;
}

void Pong::movepaddledown(Adafruit_ILI9341 &lcd)
{
    yPOMAK2 = Y1 + brzina2y;
}

void Pong::ball(Adafruit_ILI9341 &lcd, my_ballPong *b)
{

    ballX = b->startBallx;
    ballY = b->startBally;
    rb = b->r;

    lcd.fillCircle(ballX, ballY, rb, ILI9341_CYAN);
}

void Pong::moveBall(Adafruit_ILI9341 &lcd)
{
    Serial.begin(115200);

    if (ballX > lcd.width() || ballX < 0)
    {

        ballDirectionX = -ballDirectionX;
    }
    if (ballY > lcd.height() || ballY < 0)
    {

        ballDirectionY = -ballDirectionY;
    }

    ballX += ballDirectionX;

    ballY += ballDirectionY;

   // if((ballX > xPOMAK2) && (ballX < (wp + xPOMAK2)) && (ballY > yPOMAK2) && (ballY < (hp + yPOMAK2)))//ako je unutar kvadrata

    if((checkCollisionPaddle()) == true)
    {
        Serial.print("Collision");
    }
    lcd.fillCircle(ballX, ballY, rb, ILI9341_CYAN);
}

bool Pong::checkCollisionPaddle()
{
    Circledx = abs(ballX - xPOMAK2);
    Circledy = abs(ballY - yPOMAK2);


    if(Circledx > (wp/2 + rb)) return false;
    if (Circledy > (hp/2 + rb)) return false;

    if(Circledx  <= (wp/2)) return true;
    if(Circledy <= (hp/2)) return true;
    


 
}


void Pong::updateScreenGame1()
{
    requestForCallback();
}