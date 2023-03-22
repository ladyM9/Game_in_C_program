#ifndef __BALL_H__
#define __BALL_H__

#include "ILI9341_STM32.h"


typedef struct myline_t
{
    int16_t x0;
    int16_t y0;
    int16_t x1;
    int16_t y1;
};

class Ball
{
    public:
        Ball(); //konstruktor, mora biti public, defaultni konstruktor
        //Ball(int a, int b, int c); //overload konstruktor
       // void updateBallPosition(int x, int y, int X, int Y, int R);
        void updateScreen(Adafruit_ILI9341 &lcd);
        void drawCircle(int _x, int _y, int _r, uint16_t color);
        void updateBallposition(int _xCurrent, int _yCurrent);
    

    private: //kad su varijable private tu im ne daješ vrijednost
        int X;
        int Y;
        int R;
        uint16_t _color;
        int xCurrent;
        int yCurrent;
        
};

class Maze
{
    public:
        Maze();
        void updateScreen2(Adafruit_ILI9341 &lcd);
        void drawLines(myline_t _m, int _bl, uint16_t _c);
        int x0,y0,x1,y1;
        
    private:
        
        //int *p1;
        myline_t n;
        int b;
        uint16_t color1;
};



#endif