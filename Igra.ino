#include "Adafruit_GFX.h"
#include "ILI9341_STM32.h"
#include "SparkFunLSM6DS3.h"
#include "Wire.h"
#include "myDefines.h"
#include "ball.h"
#include "screen.h"
#include "paddle.h"
#include "paddleLines.h"
#include "maze.h"
#include "GUI.h"
#include "lab.h"
#include "icons.h"


// #include "GUI.h"
#define TFT_DC 9
#define TFT_CS 10
Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC);
LSM6DS3 myIMU(I2C_MODE, 0x6B); // Default constructor is I2C, addr 0x6B

Screen screen(&display);         // objekt klase Screen
Ball ball(&LCDforScreenRefresh); // objekt klase Ball
Button button(&LCDforScreenRefresh);
Maze maze; // objekt klase Maze
Pong pong(&LCDforScreenRefresh);
RNG_HandleTypeDef hrng = {0};

unsigned long Time = 0;
unsigned long Times = 0;
unsigned long TIMER_CHANGE_INTERVAL = 50000;
unsigned long millis();

int state = 0;
int brojanje_exit = 0;

void setup()
{

    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(D8, INPUT_PULLUP);
    pinMode(USER_BTN, INPUT);
    Wire.setSCL(D15);
    Wire.setSDA(D14);
    maze.initializeRNG(&hrng);
    display.begin();
    Wire.begin();
    display.setRotation(1); // rotiraj display
    Serial.begin(115200);
    myIMU.begin();
    // Forsiraj da kod misli da je partija igrice pobjeđena da bi se učitao novi random maze.
    // state = 1;
}

void loop()
{

    switch (state)
    {
    case 0:
    {
        int x;
        int y;
        button.cursor(display, 1);
        if (button.myButton(display, x, y, 150, 150, 100, 50, 3, "START", 1) == 1)
        {
            state = 1;
        }
        break;
    }
    case 1:
    {
        int x;
        int y;
        button.cursor(display, 1);
        if (button.myButton(display, x, y, 20, 90, 100, 50, 3, "Game1", 1) == 1)
        {
            state = 2;
        }
        if (button.myButton(display, x, y, 160, 90, 100, 50, 3, "Game2", 1) == 1)
        {
            state = 8;
        }

        break;
    }
    case 2:
    {
        int x;
        int y;
        int mod1 = 0;
        int mod2 = 1;
        int mod3 = 2;
        button.cursor(display, 1);                                              // prikaz kurzora u izborniku za tezinu odabrane igrice
        if (button.myButton(display, x, y, 20, 20, 100, 50, 3, "Easy", 1) == 1) // ako je kliknuta tipka za easy tezinu igrice odi na state 2
        {
            mod1 = maze.choosing_Mode_Game(0);
            state = 4;
        }
        if (button.myButton(display, x, y, 150, 20, 120, 50, 3, "Medium", 1) == 1)
        {
            mod2 = maze.choosing_Mode_Game(1);
            state = 4;
        }
        if (button.myButton(display, x, y, 100, 100, 120, 50, 3, "Hard", 1) == 1)
        {
            mod3 = maze.choosing_Mode_Game(2);
            state = 4;
        }

        break;
    }
    case 3:

    {
        maze.drawLines(display); // iscrtaj labirint na display
        Time_Game();             // iscrtaj i broji vrijeme u igrici
        GameLoop();
        if (ball.checkExit(maze.getCurrentMaze()) == true) // ako se kuglica nalazi na izlaznoj liniji iz labirinta odi na state
        {
            brojanje_exit += 1;
            state = 5;
        }

        break;
    }

    case 4:
    {
        maze.LoadNewMaze(maze.getRandomMaze(&hrng));            // ucitaj novi random labirint
        ball.firstBallposition(display, maze.getCurrentMaze()); // iscrtaj kuglicu na pocetnoj poziciji u odabranom labirintu
        Time = (millis() / 1000);                               // millis podjeli sa 1000 kako bi dobila odbrojavanje vremena u sekundama
        state = 3;                                              // odi na state 1 kako bi se odabrani random labirint iscrtao na display
        break;
    }

    case 5:
    {
        Times = (millis() / 1000);
        state = 6;

        break;
    }
    case 6:

    {
        ball.score_Game(display);
        if (brojanje_exit >= 4)
        {
            state = 7;
        }
        if (Time_Score() == true)
        {
            state = 4;
        }

        break;
    }
    case 7:
    {
        ball.win_Screen(display);
        if (Time_Score() == true)
        {
            state = 2;
        }
    }
    case 8:
    {
        pong.movePaddle(display, myIMU);
        // display.print("hELLO");
        
    }

    }

    screen.checkForRefresh();
}

void GameLoop()
{
    int n, m;
    ball.bod(display, 1, 10, 30);
    ball.collision_bod(n, m);
    ball.updateBallposition(display, myIMU);              // stalno iscrtavaj novu poziciju kuglice kako se ona pomice pomocu akceleometra
    ball.exitLine(display, maze.getCurrentMaze());        // iscrtaj na display izlaznu liniju u odabranom labirintu
    if ((ball.checkColision(maze.getCurrentMaze()) != 0)) // ako je kuglica dotaknila liniju u labirintu
    {
        ball.newBallposition(display); // kuglicu stavi na poziciju u kojoj je bila prije nego što je dotaknila liniju u labirintu
        // erial.print("Detection collision");
    }
    ball.Score(display); // poziv metode za ispis i pracenje scora u igrici
}

void Time_Game()
{
    unsigned long game_time = (millis() / 1000) - Time;
    ball.Time(display, game_time);
}

uint8_t Time_Score()
{
    uint8_t sc = false;
    unsigned long game_score = (millis() / 1000) - Times;

    ball.Time(display, game_score);
    if (game_score >= 10)
    {
        sc = true;
    }
    return sc;
    sc = false;
}

extern "C" void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    /** Supply configuration update enable
     */
    HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
    /** Configure the main internal regulator output voltage
     */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

    while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY))
    {
    }
    /** Initializes the CPU, AHB and APB busses clocks
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
    RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 1;
    RCC_OscInitStruct.PLL.PLLN = 120;
    RCC_OscInitStruct.PLL.PLLP = 2;
    RCC_OscInitStruct.PLL.PLLQ = 2;
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
    RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
    RCC_OscInitStruct.PLL.PLLFRACN = 0;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 |
                                  RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
    RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI1 | RCC_PERIPHCLK_USB | RCC_PERIPHCLK_FMC;
    PeriphClkInitStruct.FmcClockSelection = RCC_FMCCLKSOURCE_D1HCLK;
    PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
    PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Enable USB Voltage detector
     */
    HAL_PWREx_EnableUSBVoltageDetector();
}