#ifndef __MAZE_H__
#define __MAZE_H__

#include "ILI9341_STM32.h"
#include "stdio.h"
typedef struct myline_t
{
    int16_t x0;
    int16_t y0;
    int16_t x1;
    int16_t y1;
};

class Maze
{
public:
    Maze();
    // void updateScreen2(Adafruit_ILI9341 &lcd);
    void drawLines(Adafruit_ILI9341 &lcd, const myline_t *_m, int *_bl);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t _c);

    // int *p1;
    int *b;
    uint16_t color1;
    int16_t X0, Y0, X1, Y1;
    const myline_t *m;
};
#endif