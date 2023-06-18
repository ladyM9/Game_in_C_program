#include "maze.h"
#include "MyDefines.h"



myMaze_t *mazes[] = {(myMaze_t*)&lab1, (myMaze_t*)&lab2, (myMaze_t*)&lab3, (myMaze_t*)&lab4}; //polje u kojem se nalaze svi moji labirinti
Maze::Maze()
{
    color1 = ILI9341_ORANGE;
}


void Maze::drawLines(Adafruit_ILI9341 &lcd)
{
   

    for (int i = 0; i < _currentMaze->numberOfLines ; i++)
    {
        lcd.drawLine(_currentMaze->labLines[i].x0, _currentMaze->labLines[i].y0, _currentMaze->labLines[i].x1, _currentMaze->labLines[i].y1, color1); // ovako ako ne napišeš labirint ti se neće prikazati na zaslonu!!!!!
    }


    
}


void Maze::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t _c)
{
    X0 = x0;
    Y0 = y0;
    X1 = x1;
    Y1 = y1;
    color1 = _c;
}
void Maze::initializeRNG(RNG_HandleTypeDef *_hrng)
{
    // NOTE: THIS INIT FUNCTION MUST BE CALLED ONLY ONCE!

    // Enable 48MHz RC oscillator needed for Hardware Random Number Generator inside STM32.
    // First get the current STM32 oscillator settings (so we can easly modify it and enable 48MHz clock)
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    HAL_RCC_GetOscConfig(&RCC_OscInitStruct);

    // Set clock divider to 1 (do not divide the clock)
    RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;

    // Set default (factory) calibration for the 48MHz clock.
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;

    // At the end, enable the 48MHz oscillator.
    RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;

    // Apply new settings.
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    // Set RNG to use 48MHz RC oscillator as a clock source.
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RNG;
    PeriphClkInitStruct.RngClockSelection = RCC_RNGCLKSOURCE_HSI48;

    // Apply new setting to the RNG clock multiplexer.
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

    // Enable clock inside RNG.
    __HAL_RCC_RNG_CLK_ENABLE();

    // Init the RNG itself.
    // Get the instance of the RNG (get the physical address of the module inside of the STM32).
    _hrng->Instance = RNG;

    // Set clock error detection (enabled by default in CubeMX / CubeIDE).
    _hrng->Init.ClockErrorDetection = RNG_CED_ENABLE;

    // Apply settings to the RNG module.
    HAL_RNG_Init(_hrng);
}
int Maze::getNumber(RNG_HandleTypeDef *_hrng, int min, int max)
{
    uint32_t randomNumber;
    HAL_RNG_GenerateRandomNumber(_hrng, &randomNumber);

    int myRandom = (int)((double)(randomNumber) / (double)(UINT32_MAX) * (abs(min - max))) - min;

    return myRandom;
}
int Maze::LoadNewMaze(myMaze_t *_m)
{
    _currentMaze = _m;
}

myMaze_t * Maze::getRandomMaze(RNG_HandleTypeDef *_hrng)
{
    int r;
    do{
        int r = getNumber(_hrng, 0, 3);
    }while(lastRandomNumber == r);
    lastRandomNumber = r;
    
    
    return mazes[r];
    
}


