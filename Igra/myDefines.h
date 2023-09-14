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

typedef struct myPaddle_t1
{
    
    int16_t sx1;
    int16_t sy1;
    int16_t w ;
    int16_t h ;

};

typedef struct myPaddle_t2
{
    int16_t sx2;
    int16_t sy2;
    int16_t w;
    int16_t h;
};

typedef struct my_ballPong
{
    int startBallx;
    int startBally;
    int r;
};

#endif