#ifndef __BALL_H__
#define __BALL_H__

#include "ILI9341_STM32.h"
#include "stdio.h"



// int(*funcPtr)() = NULL;
typedef struct myline_t
{
    int16_t x0;
    int16_t y0;
    int16_t x1;
    int16_t y1;
};

// typedef void (ToScreenfunc)(Zaslon*);
void collision();

class Ball
{
public:
    Ball(void (*_callBack)(), void(*l)());
    // Ball(ToScreenfunc func); // konstruktor, mora biti public, defaultni konstruktor
    void drawCircle(int _x, int _y, int _r, uint16_t color);
    void updateScreen();
    // int updateBallposition(void *p,int _xCurrent, int _yCurrent);
    void updateBallposition(Adafruit_ILI9341 &lcd, int _xCurrent, int _yCurrent);
    uint8_t checkColision(const myline_t *_m, int _n);
    uint8_t checkPoint(const myline_t * _m, int _n);
    //uint8_t checkPoint(const myline_t * _m, int _n);


private: // kad su varijable private tu im ne daješ vrijednost
    int X;
    int Y;
    int R;
    uint16_t _color;
    int xCurrent;
    int yCurrent;
    int n;
    const myline_t *m;
    void (*requestForCallback)();
    void(*_l)();
    // ToScreenfunc func;
    // Zaslon*;
};

class Maze
{
public:
    Maze();
    // void updateScreen2(Adafruit_ILI9341 &lcd);
    void drawLines(Adafruit_ILI9341 &lcd, const myline_t *_m, int _bl);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t _c);

private:
    // int *p1;
    int b;
    uint16_t color1;
    int16_t X0, Y0, X1, Y1;
    const myline_t *m;
    
};


    

#endif