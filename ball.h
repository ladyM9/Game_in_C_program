#ifndef __BALL_H__
#define __BALL_H__

#include "ILI9341_STM32.h"

class Ball
{
    public:
        Ball();
        void updateBallPosition(int _x, int _y);

    private:
        int xCurrent = 0;
        int yCurrent = 0;
        int xOld = 0;
        int yOld = 0;
        int r = 2;
};

#endif