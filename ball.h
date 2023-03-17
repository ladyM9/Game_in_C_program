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
        void drawLine(int _x0, int _y0, int _x1, int _y1, uint16_t _color1);
        void drawMaze(int *p);
    private:
        int x0,y0,x1,y1;
        int *p1;
        uint16_t color1;
};



#endif