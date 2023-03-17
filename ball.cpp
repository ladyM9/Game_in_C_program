#include "ball.h"

Ball::Ball()
{
    X = 20;
    Y = 20;
    _color = ILI9341_BLUE;
    R = 2;
       
}

Maze::Maze()
{
    color1 = ILI9341_ORANGE;
    x0;
    x1;
    y0;
    y1;
    color1;
}

void Ball::updateScreen(Adafruit_ILI9341 &lcd)
{
    lcd.drawCircle(X,Y,R,_color);
    lcd.display();
    lcd.clearDisplay();
}

void Ball::drawCircle(int _x, int _y, int _r, uint16_t color)
{
    //tu pišeš što tvoja funkcija treba raditi
    X = _x;
    Y = _y;
    _color = color;
    R = _r;

}

void Ball::updateBallposition(int _xCurrent, int _yCurrent)
{
    xCurrent = _xCurrent;
    yCurrent = _yCurrent;
    drawCircle(X,Y,R,_color);
    int rawX = 1023 - analogRead(A0);
    int rawY = 1023 - analogRead(A1);

    if (rawX < 500 || rawX > 520)
    {
        xCurrent = X;
        X += (511 - rawX) / 100;
    }
    if (rawY < 500 || rawY > 520)
    {
        yCurrent = Y;
        Y += (511 - rawY) / 100;
    }

}


void Maze::drawLine(int _x0, int _y0, int _x1, int _y1, uint16_t _color1)
{
    x0 = _x0;
    y0 = _y0;
    x1 = _x1;
    y1 = _y1;
    color1 = _color1;
}



