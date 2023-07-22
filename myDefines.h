#ifndef __DEFINES_H__
#define __DEFINES_H__

typedef struct myline_t
{
    int16_t x0;
    int16_t y0;
    int16_t x1;
    int16_t y1;
};

typedef struct myMaze_t
{
    myline_t *labLines;
    int startPosX;
    int startPosY;
    myline_t endLine;
    int numberOfLines;
};

typedef struct myRect_t
{
    int16_t x;
    int16_t y;
    int16_t w;
    int16_t h;
    int16_t r;
};



#endif