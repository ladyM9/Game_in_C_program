#ifndef __PADDLE_H__
#define __PADDLE_H__

#include "ILI9341_STM32.h"
#include "Arduino.h"
#include "hal_conf_extra.h"
#include "myDefines.h"
#include "SparkFunLSM6DS3.h"


class Pong
{
public:
    Pong(void (*_callBack)());
    void paddle(Adafruit_ILI9341 &lcd);
    void drawPaddle(int16_t sx1, int16_t sy1, int16_t sx2, int16_t sy2, uint16_t _c);
    void movePaddle(Adafruit_ILI9341 &lcd, LSM6DS3 myIMU);
    void updateScreenGame1();

    int16_t Xp1, Yp1, Xp2, Yp2;
    uint16_t _colorpaddle;

private:
    myPaddle_t *p;
    void (*requestForCallback)();
    
    
    float X0,Y0,X1,Y1;
    float yPOMAK1, yPOMAK2, xPOMAK1, xPOMAK2; 
    float brzinay, brzinax;
    float brzina2x, brzina2y;
};

#endif