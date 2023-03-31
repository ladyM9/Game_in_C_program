#include "ball.h"

Ball::Ball()
{
    X = 20; //početna pozicija objekta po x i y osi, boja objekta i polumjer
    Y = 20;
    _color = ILI9341_BLUE;
    R = 2;
       
}


//void Ball::updateScreen(Adafruit_ILI9341 &lcd)
//{
  //  lcd.drawCircle(X,Y,R,_color); //ispis objekta na display
   // lcd.display();
    //lcd.clearDisplay();
//}

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
    ((Ball *)p)->drawCircle(X,Y,R, _color);
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
    return X;
    if (rawY < 500 || rawY > 520)
    {
        yCurrent = Y;
        Y += (511 - rawY) / 100;
        

    }return Y;
    
}

Maze::Maze()
{
    color1 = ILI9341_ORANGE; 
    X0 ;
    Y0 ;
    X1 ;
    Y1 ;
    b = 80;

}


void Maze::drawLines(const myline_t *_m, int _bl)
{
    b = _bl;
    for(int i = 0; i < b; i++)
    {
        drawLine(_m[i].x0, _m[i].y0, _m[i].x1, _m[i].y1, color1);
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

Zaslon::Zaslon()
{
    
}
void Zaslon::updateScreen(Adafruit_ILI9341 &lcd)
{
   // k = l;
    
    //if (funcPtr !=  NULL)
    //{
      //  funcPtr(X,Y);
       // lcd.display();
    //}
    lcd.display();
}
void Zaslon::run()
{
    fptr p = &(Ball::updateBallposition);
    (mb->*p)(X,Y);
}

//void Zaslon::ispis(Ball* ball, void (Ball::* drawCircle)(int _x, int _y, int _r, uint16_t color))
//{
    
  //  (ball->*drawCircle)(2,3,2,ILI9341_BLUE);
//}
//void Zaslon::myFunction(funcPtr cb,void *p)
//{
   // m_cb = cb;
   // m_p = p;
//}

//void Zaslon::myFunction(int(*func)(int,int))
//{
    
  //  funcPtr = func;//pokazivač koji pokazuje na drugu funkciju
//}







