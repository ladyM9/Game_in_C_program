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
    int myButton(Adafruit_ILI9341 &lcd, int _xcur, int _ycur, int x, int y, int h, int w, int _textscale, char *mytext, int draw);
    void cursor(Adafruit_ILI9341 &lcd, int draw_cursor);

private:
    int16_t X, Y, W, H, r;
    int xp, yp;
    int xc, yc;
    float rp;
    void (*request)();
};

#endif