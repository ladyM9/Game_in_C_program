#ifndef __DEFINES_H__
#define __DEFINES_H__

typedef struct myline_t //tip podatka za liniju u polju, njen x0,y0,x1,y1
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

typedef struct myRect_t //tip podatka za kvadrat odnosno tipku u izborniku
{
    int16_t x;
    int16_t y;
    int16_t w;
    int16_t h;
    int16_t r;
};

typedef struct myPaddle_t1 //tip podatka za reket kojim upravlja korisnik
{
    
    int16_t sx1; //pozicija po x osi
    int16_t sy1;  //pozicija po y osi
    int16_t w ; //sirina reketa
    int16_t h ; //visina reketa

};
 
typedef struct myPaddle_t2 //tip podatka za reket kojim upravlja mikroupravljač
{
    int16_t sx2; 
    int16_t sy2;
    int16_t w;
    int16_t h;
};

typedef struct my_ballPong //tip podatka za kuglicu u igri pong
{
    int startBallx; //pozicija kuglice po x osi
    int startBally; //pozicija kuglice po y osi
    int r; //radius kuglice
};

#endif