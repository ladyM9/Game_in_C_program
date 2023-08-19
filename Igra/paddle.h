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
    void paddle1(Adafruit_ILI9341 &lcd, myPaddle_t1 *p1);
    void paddle2(Adafruit_ILI9341 &lcd, myPaddle_t2 *p2);
    void movePaddle1(Adafruit_ILI9341 &lcd, LSM6DS3 myIMU);
    void movepaddleup(Adafruit_ILI9341 &lcd);
    void movepaddledown(Adafruit_ILI9341 &lcd);
    void movePaddle2(Adafruit_ILI9341 &lcd);
    void ball(Adafruit_ILI9341 &lcd,  my_ballPong *b);
    void moveBall(Adafruit_ILI9341 &lcd);
    bool checkCollisionPaddle();
    //int x, int y, int rectX, int rectY, int rectWidth, int rectHeight
    void updateScreenGame1();

    uint16_t _colorpaddle;

private:
    void (*requestForCallback)();

    int16_t wp, hp;
    float X0, Y0, X1, Y1;
    float yPOMAK1, yPOMAK2, xPOMAK1, xPOMAK2, rb;
    float brzinay, brzinax;
    float brzina2x, brzina2y;
    int ballDirectionX = 2;
    int ballDirectionY = 2;
    int ballX, ballY, oldBallX, oldBallY;
    float Circledx, Circledy;
    int16_t xb, yb;
};

#endif