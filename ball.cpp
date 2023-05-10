#include "ball.h"
#include "screen.h"
#include "maze.h"

Ball::Ball(void (*_callBack)())
{
    X = 18; // početna pozicija objekta po x i y osi, boja objekta i polumjer
    Y = 18;
    _color = ILI9341_BLUE;
    R = 2;
    n = 120;

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
    // lcd.drawCircle(X, Y, R, _color);
    //  checkColision(const myline_t *_m, n);
    int rawX = 1023 - analogRead(A0);
    int rawY = 1023 - analogRead(A1);
    lcd.drawCircle(X, Y, R, _color); // ispisivanje kuglice na početnoj poziciji

    xOld = X;
    yOld = Y;
    X += (511 - rawX) / 100;
    Y += (511 - rawY) / 100;
    Serial.print(rawX);

    checkColision(m, n);


    updateScreen();
}

void Ball::checkColision(const myline_t *_m, int _n) //_m je pokazivač na polje, a _n koliko linija imaš u polju
{

    m = _m;
    n = _n;

    myline_t p[120]; // ako tu ne deklariraš polje ova funkcija unutar klase ne vidi polje koje se nalazi u klasi Maze u metodi drawLines
    m = p;           // pokazivač na polje

    drawLine(X0, Y0, X1, Y1, color1);
    drawCircle(X, Y, R, _color); // poziv funkcije drawCircle, moraš ju pozvat jer ova metoda inaće ne vidi X,Y od Circle
    // updateBallposition(Adafruit_ILI9341 &lcd, int _xCurrent, int _yCurrent);
    // uint 8_t checkCollision(const myline_t *_l, int _n) // detekcija kolizije, odnosno da li je objekt dodirnuo liniju u labirintu
    uint8_t _cd;

    for (int i = 0; i < 120; i++)
    {
        _cd = false;
        int _w = abs(p[i].x1 - p[i].x0);
        int _h = abs(p[i].y1 - p[i].y0);
        int _x = p[i].x0 >= p[i].x1 ? p[i].x1 : p[i].x0; // ovo si prije radila u void loop petlji sa ispitivanjem if (col %ss 1) i ( col % 2)
        int _y = p[i].y0 >= p[i].y1 ? p[i].y1 : p[i].y0;
        if ((_w != 0) && (X >= _x) && (X < (_x + _w)))
        {
            if (((yOld >= _y) && (Y <= _y)) || (yOld <= _y) && (Y >= _y))
            {
                _cd = true;
                X = xOld;
                Y = yOld;
                drawCircle(X, Y, R, ILI9341_GREEN);
                // Serial.printf("Colision y\n");
            }
        }
        _cd = false;
        

        if ((_h != 0) && (Y >= _y) && (Y < (_y + _h)))
        {
            if (((xOld >= _x) && (X <= _x)) || ((xOld <= _x) && (X >= _x)))
            {

                _cd = true;
                X = xOld;
                Y = yOld;
                drawCircle(X, Y, R, ILI9341_MAGENTA);
                // Serial.printf("Colision x");
            }
        }
        _cd = false;
        
    }

    // return _cd;
}