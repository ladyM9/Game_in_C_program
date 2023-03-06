#include "ball.h"

Ball::Ball():
:xCurrent(1),

{
        
}


void Ball::updateBallPosition(int _x, int _y)
{
    xOld = xCurrent;
    yOld = yCurrent;

    xCurrent = _x;
    yCurrent = _y;
}