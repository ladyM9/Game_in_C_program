#ifndef __BALL_H__
#define __BALL_H__

#include "ILI9341_STM32.h"
#include "stdio.h"
#include "maze.h"

// int(*funcPtr)() = NULL;
// typedef void (ToScreenfunc)(Zaslon*);

class Ball: public Maze
{
public:
    Ball(void (*_callBack)());
    // Ball(ToScreenfunc func); // konstruktor, mora biti public, defaultni konstruktor
    void drawCircle(int _x, int _y, int _r, uint16_t color);
    void updateScreen();
    // int updateBallposition(void *p,int _xCurrent, int _yCurrent);
    void updateBallposition(Adafruit_ILI9341 &lcd, int _xCurrent, int _yCurrent);
    uint8_t checkColision(const myline_t *_m, int _n);
  
    //uint8_t checkPoint(const myline_t * _m, int _n);


private: // kad su varijable private tu im ne daješ vrijednost
    int X,X1, xOld;
    int Y,Y1, yOld;
    int R, pr;
    int xs,ys,rs;
    uint16_t _color, početnaB, cs;
    int xCurrent;
    int yCurrent;
    int n;
    const myline_t *m;
    void (*requestForCallback)();
    void(*_l)();

    // ToScreenfunc func;
    // Zaslon*;
};

#endif