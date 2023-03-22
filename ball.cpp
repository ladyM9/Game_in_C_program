#include "ball.h"

Ball::Ball()
{
    X = 20; //početna pozicija objekta po x i y osi, boja objekta i polumjer
    Y = 20;
    _color = ILI9341_BLUE;
    R = 2;
       
}


void Ball::updateScreen(Adafruit_ILI9341 &lcd)
{
    lcd.drawCircle(X,Y,R,_color); //ispis objekta na display
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
Maze::Maze()
{
    color1 = ILI9341_ORANGE; 
    b = 80;
    n;
}
void Maze::updateScreen2(Adafruit_ILI9341 &lcd)
{
    lcd.drawLine(x0,y0,x1,y1,color1);
    lcd.display();
}


void Maze::drawLines(myline_t _m, int _bl, uint16_t _c)
{
    color1 = _c;
    b = _bl;
    n = _m;
}



 