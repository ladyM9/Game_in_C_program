#ifndef __DEFINES_H__
#define __DEFINES_H__

typedef struct myline_t
{
    int16_t x0;
    int16_t y0;
    int16_t x1;
    int16_t y1;
};

typedef struct OBJECT_t {
  int x ;
  int y ;
  int xOld ;
  int yOld ;
  int r = 2;
  int O = 2 * r * 3.14;
};

#endif
