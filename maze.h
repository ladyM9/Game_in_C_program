#ifndef __MAZE_H__
#define __MAZE_H__

#include "ILI9341_STM32.h"
#include "Arduino.h"
#include "ball.h"
#include "screen.h"
#include "hal_conf_extra.h"
#include "lab.h"
#include "myDefines.h"
#define offset_x  20
#define offset_y  20


class Maze
{
public:
    Maze();
    void drawLines(Adafruit_ILI9341 &lcd);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t _c);
    void initializeRNG(RNG_HandleTypeDef *_hrng);
    int getNumber(RNG_HandleTypeDef *_hrng, int min, int max);
    void LoadNewMaze(myMaze_t *_m);
    myMaze_t *getRandomMaze(RNG_HandleTypeDef *_hrng);
    myMaze_t *getCurrentMaze();
    void choosingaMaze(Adafruit_ILI9341 &lcd);

    uint16_t color1;
    int16_t X0, Y0, X1, Y1;

    int16_t BRel;

private:
    int lastRandomNumber = 0;
    myMaze_t *_currentMaze;
    myMaze_t *easyLab[50];
    int *b;
};
#endif