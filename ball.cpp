#include "ball.h"
#include "screen.h"
#include "maze.h"

Ball::Ball(void (*_callBack)())
{

    X = 18; // početna pozicija objekta po x i y osi, boja objekta i polumjer
    Y = 18;
    _color = ILI9341_BLUE;
    R = 2;
    b = 80;


    requestForCallback = _callBack;
}

void Ball::updateScreen()
{
    requestForCallback();
}


void Ball::updateBallposition(Adafruit_ILI9341 &lcd)
{
    //((Ball *)p)->drawCircle(X,Y,R, _color);
    //xCurrent = _xCurrent;
    //yCurrent = _yCurrent;

    // lcd.drawCircle(X, Y, R, _color);
    //  checkColision(const myline_t *_m, n);
    int rawX = 1023 - analogRead(A0);
    int rawY = 1023 - analogRead(A1);
    xCurrent = X;
    yCurrent = Y;
    X += (511 - rawX) / 100;
    Y += (511 - rawY) / 100;
    
    lcd.fillCircle(X, Y, R, _color); // ispisivanje kuglice na početnoj poziciji, tu mora pisat ovo( NEPREMJEŠTAJ INAĆE SE NEĆE ISPISAT NA DISPLAY)
    updateScreen();
}


uint8_t Ball::checkColision(const myline_t *_m, int _b1) //_m je pokazivač na polje, a _n koliko linija imaš u polju
{
    // updateBallposition(Adafruit_ILI9341 &lcd, int _xCurrent, int _yCurrent);
    // uint 8_t checkCollision(const myline_t *_l, int _n) // detekcija kolizije, odnosno da li je objekt dodirnuo liniju u labirintu
    uint8_t _cd = false;

    for (int i = 0; i < b; i++)
    {
        int _w = abs(m[i].x0 - m[i].x0);
        int _h = abs(m[i].y1 - m[i].y0);
        int _x = m[i].x0 >= m[i].x1 ? m[i].x1 : m[i].x0; // ovo si prije radila u void loop petlji sa ispitivanjem if (col %ss 1) i ( col % 2)
        int _y = m[i].y0 >= m[i].y1 ? m[i].y1 : m[i].y0;

        if ((_w != 0) && (X >= _x) && (X < (_x + _w)))
        {
            if (((yCurrent >= _y) && (Y <= _y)) || (yCurrent <= _y) && (Y >= _y)) _cd |= true;  
                  
                // Serial.printf("Colision y\n");
        }

        if ((_h != 0) && (Y >= _y) && (Y < (_y + _h)))
        {
            if (((xCurrent >= _x) && (X <= _x)) || ((xCurrent <= _x) && (X >= _x)))  _cd |= true; 
                      // Serial.printf("Colision x"); 
        }
    }
    return _cd;
}