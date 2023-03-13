#ifndef __BALL_H__
#define __BALL_H__

#include "ILI9341_STM32.h"

class Ball
{
    public:
        Ball(); //konstruktor, mora biti public, defaultni konstruktor
        //Ball(int a, int b, int c); //overload konstruktor
       // void updateBallPosition(int x, int y, int X, int Y, int R);
        void updateScreen(Adafruit_ILI9341 &lcd);
        void drawCircle(int _x, int _y, int _r, uint16_t color);
        void updateBallposition(int _x, int _y);
    

    private: //kad su varijable private tu im ne daješ vrijednost
        int xCurrent;
        int yCurrent;
        int xOld ;
        int yOld ;
        int _r ;
        int _y;
        int _x;
        int X;
        int Y;
        int R;
        uint16_t color;
        uint16_t C;
};

#endif