#include "ball.h"


Ball::Ball() //tu ne ide točka zarez
{
     xOld; // ne valja
     yOld;
     r;
}
void Ball::updateBallPosition(int x, int y, int X, int Y, int R)

{
    int rawX = 1023 - analogRead(A0);
    int rawY = 1023 - analogRead(A1);

    //xOld = X;
    //yOld = Y;
    //r = R;

    xCurrent = x;
    yCurrent = y;
    xOld = X;
    yOld = Y;
    r = R;
    if (rawX < 500 || rawX > 520)
    {
        xCurrent += (511 - rawX) / 100;
    }
    if (rawY < 500 || rawY > 520)
    {
        yCurrent+= (511 - rawY) / 100;
    }
  
}
void Ball::updateScreen(Adafruit_ILI9341&lcd)
{
    lcd.display();
}

void Ball::drawCircle(int _x,int _y,uint16_t c)
{
    _x = 2;
    _y = 2;
    c = ILI9341_WHITE;
}

