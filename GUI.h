#ifndef __GUI_H__
#define __GUI_H__

#include "ILI9341_STM32.h"
#include "Arduino.h"
#include "stdio.h"
#include "myDefines.h"

class Button
{
    public:
    Button(void (*_call)());
    void updateFirstScreen();
    void startScreen(Adafruit_ILI9341 &lcd);
    void drawRectangle(int16_t x, int16_t y, int16_t w, int16_t h );
    void ball(Adafruit_ILI9341 &lcd);
    void ballposition(Adafruit_ILI9341 &lcd);
    void newposition(Adafruit_ILI9341 &lcd);



    private:
    int16_t X,Y,W,H, r;
    int xp, yp;
    int xc, yc;
    float rp;
    void (*request)();


};


#endif