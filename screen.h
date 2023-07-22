#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "ILI9341_STM32.h"

void LCDforScreenRefresh(); //ovu funkciju povezujem sa klasom Ball i Button

//klasa za zaslon, u njoj se nalazi metoda za osvježavanje zaslona
class Screen
{
public:
    Screen(Adafruit_ILI9341 *lcd);
    //void passCallbackToMe(Ball *ball, void (Ball::*updateBallposition)(Adafruit_ILI9341 &lcd, int _xCurrent, int _yCurrent));
    void checkForRefresh();

private:
   Adafruit_ILI9341 *_lcd;
};

#endif