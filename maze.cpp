#include "maze.h"
#include "ball.h"
#include "screen.h"

Maze::Maze()
{
    color1 = ILI9341_ORANGE;
    X0;
    Y0;
    X1;
    Y1;
}


void Maze::drawLines(Adafruit_ILI9341 &lcd, const myline_t *_m, int *_bl)
{
   
    b = _bl;
    m = _m;
    int a;
    int br = elements(BRel);
    for (int i = 0; i < b[br] ; i++)
    {
        lcd.drawLine(m[i].x0, m[i].y0, m[i].x1, m[i].y1, color1); // ovako ako ne napišeš labirint ti se neće prikazati na zaslonu!!!!!
    }
    
}

int Maze::elements(int16_t _Brel)
{
    BRel = _Brel;
    int i;
    BRel = (sizeof(m[i])) / (sizeof(myline_t));
    return BRel;
}

void Maze::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t _c)
{
    X0 = x0;
    Y0 = y0;
    X1 = x1;
    Y1 = y1;
    color1 = _c;
}

