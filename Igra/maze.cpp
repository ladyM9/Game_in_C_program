#include "maze.h"
#include "GUI.h"

myMaze_t *mazes_easy[] = {(myMaze_t *)&lab2, (myMaze_t *)&lab1, (myMaze_t *)&lab3, (myMaze_t *)&lab4};
myMaze_t *mazes_medium[] = {(myMaze_t *)&lab6, (myMaze_t *)&lab7, (myMaze_t *)&lab8, (myMaze_t *)&lab9};
myMaze_t *mazes_hard[] = {(myMaze_t *)&lab11, (myMaze_t *)&lab12, (myMaze_t *)&lab13};

Maze::Maze()
{
    color1 = ILI9341_ORANGE; // boja svakog labirinta
}

void Maze::drawLines(Adafruit_ILI9341 &lcd) // metoda pomocu koje se iscrtavaju sve linije iz pojedinog labirinta na display
{
    if (_currentMaze == NULL)
        return;

    for (int i = 0; i < _currentMaze->numberOfLines; i++)
    {
        lcd.setRotation(3);
        lcd.drawLine(_currentMaze->labLines[i].x0, _currentMaze->labLines[i].y0 + offset_y, _currentMaze->labLines[i].x1, _currentMaze->labLines[i].y1 + offset_y, color1); // ovako ako ne napiĹˇeĹˇ labirint ti se neÄ‡e prikazati na zaslonu!!!!!
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
void Maze::LoadNewMaze(myMaze_t *_m)
{
    _currentMaze = _m;
}

int Maze::choosing_Mode_Game(int mode_g)
{
    if (mode_g == 0)
    {
        mode_game = 0;
    }
    if (mode_g == 1)
    {
        mode_game = 1;
    }
    if (mode_g == 2)
    {
        mode_game = 2;
    }
    
    return mode_game;
}

myMaze_t *Maze::getRandomMaze(RNG_HandleTypeDef *_hrng)
{
    int choose;
    int r;
    if (mode_game == 0)
    {
        do
        {
            r = getNumber(_hrng, 0, sizeof(mazes_easy) / sizeof(myMaze_t *));
        } while (lastRandomNumber == r);
        lastRandomNumber = r;
        return mazes_easy[r];
    }
    if (mode_game == 1)
    {
        {
            do
            {
                r = getNumber(_hrng, 0, sizeof(mazes_medium) / sizeof(myMaze_t *));
            } while (lastRandomNumber == r);
            lastRandomNumber = r;
            return mazes_medium[r];
        }
    }
    if (mode_game == 2)
    {
        {
            do
            {
                r = getNumber(_hrng, 0, sizeof(mazes_hard) / sizeof(myMaze_t *));
            } while (lastRandomNumber == r);
            lastRandomNumber = r;
            return mazes_hard[r];
        }
    }
}

myMaze_t *Maze::getCurrentMaze()
{
    return _currentMaze;
}