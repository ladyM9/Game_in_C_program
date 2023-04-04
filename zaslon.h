#ifndef __ZASLON_H__
#define __ZASLON_H__

#include "ILI9341_STM32.h"

void LCDrequestForRefresh();

class Zaslon
{
    public:
        Zaslon(Adafruit_ILI9341 *lcd);
        void checkForRefresh();

    private:
        Adafruit_ILI9341 *_lcd;
};

#endif