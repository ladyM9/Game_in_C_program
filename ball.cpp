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

    uint8_t Xnew, Ynew;
    Xnew = xOld;
    Ynew = yOld;
    uint8_t rez = 0;
    uint8_t rez1 = 1;
    uint8_t rez2 = 2;

    uint8_t col = checkColision(m, n);
    bool cold = false;
    bool ref = false;

    if (rawX < 500 || rawX > 520)
    {
          X += (511 - rawX) / 100;
       

    }
    if (rawY < 500 || rawY > 520)
    {
          Y += (511 - rawY) / 100;
          
    }
    if(col == rez1)
    {
        cold = true;
        X = Xnew;
        drawCircle(X,Y,R, ILI9341_DARKGREEN);
    }
    cold = false;
    drawCircle(X,Y,R,_color);



    updateScreen();
}

uint8_t Ball::checkColision(const myline_t *_m, int _n) //_m je pokazivač na polje, a _n koliko linija imaš u polju
{

    m = _m;
    n = _n;

    myline_t p[120]; // ako tu ne deklariraš polje ova funkcija unutar klase ne vidi polje koje se nalazi u klasi Maze u metodi drawLines
    m = p;           // pokazivač na polje

    drawLine(X0, Y0, X1, Y1, color1);
    drawCircle(X, Y, R, _color); // poziv funkcije drawCircle, moraš ju pozvat jer ova metoda inaće ne vidi X,Y od Circle
    // updateBallposition(Adafruit_ILI9341 &lcd, int _xCurrent, int _yCurrent);
    // uint 8_t checkCollision(const myline_t *_l, int _n) // detekcija kolizije, odnosno da li je objekt dodirnuo liniju u labirintu
    uint8_t _cd = 0;

    for (int i = 0; i < 120; i++)
    {
        int _w = abs(p[i].x1 - p[i].x0);
        int _h = abs(p[i].y1 - p[i].y0);
        int _xos = p[i].x0 >= p[i].x1 ? p[i].x1 : p[i].x0; // ovo si prije radila u void loop petlji sa ispitivanjem if (col %ss 1) i ( col % 2)
        int _yos = p[i].y0 >= p[i].y1 ? p[i].y1 : p[i].y0;
        if ((_w != 0) && (X >= _xos) && (X < (_xos + _w)))
        {
            if (((yOld >= _yos) && (Y <= _yos)) || (yOld <= _yos) && (Y >= _yos))
            {
                _cd = 1;
            
                
                // Serial.printf("Colision y\n");
            }
        }
        
        

        if ((_h != 0) && (Y >= _yos) && (Y < (_yos + _h)))
        {
            if (((xOld >= _xos) && (X <= _xos)) || ((xOld <= _xos) && (X >= _xos)))
            {

                _cd = 2;
           
                
                // Serial.printf("Colision x");
            }
        }
        
        
    }

    return _cd;
}