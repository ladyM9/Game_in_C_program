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
    void movePaddle1(Adafruit_ILI9341 &lcd, LSM6DS3 myIMU, myPaddle_t1 *p1);
    void movepaddleup(Adafruit_ILI9341 &lcd);
    void movepaddledown(Adafruit_ILI9341 &lcd);
    void movePaddle2(Adafruit_ILI9341 &lcd, myPaddle_t2 *p2, my_ballPong *b);
    void ball(Adafruit_ILI9341 &lcd,  my_ballPong *b);
    void moveBall(Adafruit_ILI9341 &lcd, my_ballPong *b);
    uint8_t checkCollisionPaddle(myPaddle_t1 *p1, myPaddle_t2 *p2, my_ballPong *b);
    void newBallPosition(my_ballPong *b);
    uint8_t GAME_OVER(Adafruit_ILI9341 &lcd);
    void gameOverText(Adafruit_ILI9341 &lcd);
    void scoreInGame(Adafruit_ILI9341 &lcd);
    void scoreInGame2(Adafruit_ILI9341 &lcd);
    uint8_t live_User(Adafruit_ILI9341 &lcd);
    uint8_t lives_minus();
  
    //int x, int y, int rectX, int rectY, int rectWidth, int rectHeight
    void updateScreenGame1();

    uint16_t _colorpaddle;

private:
    void (*requestForCallback)();


    float X0, Y0, X1, Y1;
    int newxb, newyb;
    int Xb,Yb;
    uint8_t score = false;
    uint8_t score2 = false;
    uint8_t score1 = score;
    uint8_t score3 = score2;
    uint8_t live = 5;  //zivoti korisnika koji igra igricu
    uint8_t live_rac = 5; //zivoti racunala
    uint8_t game_over = false;
    uint8_t gm = false;
    float brzinay, brzinax;
    float brzina2x, brzina2y;
    int ballDirectionX = 2;  //brzina kretanja kuglice u smjeru x
    int ballDirectionY = 2; //brzina kretanja kuglice u smjeru y
};

#endif