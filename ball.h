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

class Ball
{
public:
    Ball();
    // Ball(ToScreenfunc func); // konstruktor, mora biti public, defaultni konstruktor
    //  Ball(int a, int b, int c); //overload konstruktor
    //  void updateBallPosition(int x, int y, int X, int Y, int R);
    void updateScreen(Adafruit_ILI9341 &lcd);
    void drawCircle(int _x, int _y, int _r, uint16_t color);
    // int updateBallposition(void *p,int _xCurrent, int _yCurrent);
    void updateBallposition(int _xCurrent, int _yCurrent);
    

private: // kad su varijable private tu im ne daješ vrijednost
    int X;
    int Y;
    int R;
    uint16_t _color;
    int xCurrent;
    int yCurrent;
    // ToScreenfunc func;
    // Zaslon*;
};

class Maze
{
public:
    Maze();
    // void updateScreen2(Adafruit_ILI9341 &lcd);
    void drawLines(const myline_t *_m, int _bl);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t _c);

private:
    // int *p1;
    int b;
    uint16_t color1;
    int16_t X0, Y0, X1, Y1;
};

class Zaslon
{
public:
    void passCallbackToMe(Ball *ball, void (Ball::*updateScreen2)(Adafruit_ILI9341 &lcd));

private:
    Adafruit_ILI9341 &l;
    
};

#endif