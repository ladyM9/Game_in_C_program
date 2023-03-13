#include "ball.h"

Ball::Ball()
{
    int _x = 20;
    int _y = 20;
    uint16_t color = ILI9341_BLUE;
    int _r = 2;

}

void Ball::updateScreen(Adafruit_ILI9341 &lcd)
{
     lcd.display();
     lcd.drawCircle(20,20,2,ILI9341_BLUE);
}

void Ball::drawCircle(int _x, int _y, int _r, uint16_t color) 
{
    //tu pišeš što tvoja funkcija treba raditi
   // X = _x;
    //Y = _y;
   // C = color;
   // _r = R;
   // Ball lcd;
   // lcd.drawCircle(_x, _y,color);
   _x = 20;
   _y = 20;
   _r = 2;
   color = ILI9341_BLUE;

}

void Ball::updateBallposition(int _x, int _y)
{
    int rawX = 1023 - analogRead(A0);
    int rawY = 1023 - analogRead(A1);
    xCurrent = _x;
    yCurrent = _y;

    if (rawX < 500 || rawX > 520)
    {
        _x = xCurrent;
        xCurrent += (511 - rawX) / 100;
    }

}


