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
    void updateScreen();
    // int updateBallposition(void *p,int _xCurrent, int _yCurrent);
    void updateBallposition(Adafruit_ILI9341 &lcd);
    uint8_t checkColision(const myline_t *_m,int *_b1);
    uint8_t checkExit(const myline_t *_e, int *_lin);
    void loadMaze(const myline_t *_ol, int *_br);
    void newBallposition(Adafruit_ILI9341 &lcd);
    void exitLine(Adafruit_ILI9341 &lcd, const myline_t *_e, int *_lin);
    void Time(Adafruit_ILI9341 &lcd);
       // void loadMaze(const myline_t *_m, const int *b1);
  
    //uint8_t checkPoint(const myline_t * _m, int _n);


private: // kad su varijable private tu im ne daješ vrijednost
    int X;
    int Y;
    int R;
    uint16_t _color;
    int xCurrent;
    int yCurrent;
    int *b;
    const myline_t *m;
    const myline_t *e;
    int *lin;
    void (*requestForCallback)();
    void(*_l)();

    // ToScreenfunc func;
    // Zaslon*;
};

#endif