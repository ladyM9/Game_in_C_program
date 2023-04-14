#include "ball.h"
#include "screen.h"

Ball::Ball(void (*_callBack)())
{
    X = 20; // početna pozicija objekta po x i y osi, boja objekta i polumjer
    Y = 20;
    _color = ILI9341_BLUE;
    R = 2;
    n = 80;
    

    requestForCallback = _callBack;
}

void Ball::updateScreen()
{
    requestForCallback();
}

void Ball::drawCircle(int _x, int _y, int _r, uint16_t color)
{
    // tu pišeš što tvoja funkcija treba raditi
    X = _x;
    Y = _y;
    _color = color;
    R = _r;
}

void Ball::updateBallposition(Adafruit_ILI9341 &lcd, int _xCurrent, int _yCurrent)
{
    //((Ball *)p)->drawCircle(X,Y,R, _color);
    xCurrent = _xCurrent;
    yCurrent = _yCurrent;
    lcd.drawCircle(X, Y, R, _color);
    int col = checkColision(constmyline_t *_m, n);
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
    if (col !=0)
    {
        X = xCurrent;
        Y = yCurrent;
    }
    updateScreen();
}

uint8_t Ball::checkColision(const myline_t *_m, int _n)
{

    n = _n;
    drawCircle(X, Y, R, _color);
    // updateBallposition(Adafruit_ILI9341 &lcd, int _xCurrent, int _yCurrent);
    // uint8_t checkCollision(const myline_t *_l, int _n) // detekcija kolizije, odnosno da li je objekt dodirnuo liniju u labirintu

    uint8_t _cd = 0;

    for (int i = 0; i < n; i++)
    {
        int _w = abs(_m[i].x1 - _m[i].x0);
        int _h = abs(_m[i].y1 - _m[i].y0);
        int _x = _m[i].x0 >= _m[i].x1 ? _m[i].x1 : _m[i].x0; // ovo si prije radila u void loop petlji sa ispitivanjem if (col %ss 1) i ( col % 2)
        int _y = _m[i].y0 >= _m[i].y1 ? _m[i].y1 : _m[i].y0;
        if ((_w != 0) && (X >= _x) && (X < (_x + _w)))
        {
            if (((yCurrent >= _y) && (Y <= _y)) || (yCurrent <= _y) && (Y >= _y))
                _cd |= 1;
        }
        if ((_h != 0) && (Y >= _y) && (Y < (_y + _h)))
        {
            if (((xCurrent >= _x) && (X <= _x)) || ((xCurrent <= _x) && (X >= _x)))
                _cd |= 2;
        }

        return _cd;
    }
}

Maze::Maze()
{
    color1 = ILI9341_ORANGE;
    X0;
    Y0;
    X1;
    Y1;
    b = 80;
}

void Maze::drawLines(Adafruit_ILI9341 &lcd, const myline_t *_m, int _bl)
{
    b = _bl;
    for (int i = 0; i < b; i++)
    {
        lcd.drawLine(_m[i].x0, _m[i].y0, _m[i].x1, _m[i].y1, color1);
    };
}

void Maze::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t _c)
{
    X0 = x0;
    Y0 = y0;
    X1 = x1;
    Y1 = y1;
    color1 = _c;
}
