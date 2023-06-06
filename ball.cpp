#include "ball.h"
#include "screen.h"
#include "maze.h"


Ball::Ball(void (*_callBack)())
{

    //X = 18; // početna pozicija objekta po x i y osi, boja objekta i polumjer
    //Y = 18;
    X = 150; //početna pozicija kuglice tj objekta na X osi
    Y = 2;
    _color = ILI9341_BLUE;
    R = 2;
    requestForCallback = _callBack; 
}

void Ball::updateScreen()
{
    requestForCallback();
}


void Ball::updateBallposition(Adafruit_ILI9341 &lcd)
{

    int rawX = 1023 - analogRead(A0);
    int rawY = 1023 - analogRead(A1);
    xCurrent = X;
    yCurrent = Y;
    X += (511 - rawX) / 100;
    Y += (511 - rawY) / 100;
    
    lcd.fillCircle(X, Y, R, _color); // ispisivanje kuglice na početnoj poziciji, tu mora pisat ovo( NEPREMJEŠTAJ INAĆE SE NEĆE ISPISAT NA DISPLAY)
    updateScreen();
}
void Ball::loadMaze(const myline_t *_ol, int *_br)
{

    m = _ol;

}


uint8_t Ball::checkColision(const myline_t *_m,int *_b1) //_m je pokazivač na polje, a _n koliko linija imaš u polju
{
    m = _m;
    b = _b1;
    uint8_t _cd = 0;
    int a;

    for (int i = 0; i < b[a]; i++)
    {
        int _w = abs(m[i].x1 - m[i].x0);
        int _h = abs(m[i].y1 - m[i].y0);
        int _x = m[i].x0 >= m[i].x1 ? m[i].x1 : m[i].x0; // ovo si prije radila u void loop petlji sa ispitivanjem if (col %ss 1) i ( col % 2)
        int _y = m[i].y0 >= m[i].y1 ? m[i].y1 : m[i].y0;

        if ((_w != 0) && (X >= _x) && (X < (_x + _w)))
        {
            if (((yCurrent >= _y) && (Y <= _y)) || (yCurrent <= _y) && (Y >= _y)) 
            {
                _cd |= 1;  
            }      
            
        }

        if ((_h != 0) && (Y >= _y) && (Y < (_y + _h)))
        {
            if (((xCurrent >= _x) && (X <= _x)) || ((xCurrent <= _x) && (X >= _x)))  _cd |= 2; 
                    
        }
    }
    return _cd;
}

 uint8_t Ball::checkExit(const myline_t *_e, int *_lin)
 {
    e = _e;
    lin = _lin;
    uint8_t _el = false;
    for (int i = 0; i < lin[0]; i++)
    {
        int _w = abs(e[i].x1 - e[i].x0);
        int _h = abs(e[i].y1 - e[i].y0);
        int _x = e[i].x0 >= e[i].x1 ? e[i].x1 : e[i].x0; // ovo si prije radila u void loop petlji sa ispitivanjem if (col %ss 1) i ( col % 2)
        int _y = e[i].y0 >= e[i].y1 ? e[i].y1 : e[i].y0;
        if ((_w != 0) && (X >= _x) && (X < (_x + _w)))
        {
            if (((yCurrent >= _y) && (Y <= _y)) || (yCurrent <= _y) && (Y >= _y)) 
            {
                _el |= true;
                
            }
            else
            {
                _el |= false;
            }      
        }
    }
    return _el;
 }

void Ball::newBallposition(Adafruit_ILI9341 &lcd)
{
    X = xCurrent;
    Y = yCurrent;
    lcd.fillCircle(X,Y,R, ILI9341_GREEN);
}
void Ball::exitLine(Adafruit_ILI9341 &lcd, const myline_t *_e, int *_lin)
{
    e = _e;
    lin = _lin;
    for (int i = 0; i < lin[0] ; i++)
    {
        lcd.drawLine(e[i].x0, e[i].y0, e[i].x1, e[i].y1, ILI9341_MAGENTA); // ovako ako ne napišeš labirint ti se neće prikazati na zaslonu!!!!!
    }
}


uint8_t Ball::Time(Adafruit_ILI9341 &lcd)
{
    unsigned long _mytime;
    unsigned long _seconds;
    uint8_t game_over;
    unsigned long millis();
    _mytime = (millis() /1000);
    _seconds = (millis() /1000);
    game_over = false;
    lcd.setCursor(15, 15);
    lcd.setTextColor(ILI9341_GREEN);
    lcd.setTextSize(3);
    lcd.printf("%2ld", (unsigned long)(_mytime));
    if(_mytime >= 40)
    {
        game_over = true;
    }
    return game_over;
}

