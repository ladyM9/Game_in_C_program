#include "Adafruit_GFX.h"
#include "ILI9341_STM32.h"
#include "myDefines.h"
#include "ball.h"
#include "screen.h"
#include "maze.h"
#include "GUI.h"
#include "lab.h"



// #include "GUI.h"
#define TFT_DC 9
#define TFT_CS 10
Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC);

Screen screen(&display);         // objekt klase Screen
Ball ball(&LCDforScreenRefresh); // objekt klase Ball
Maze maze;                       // objekt klase Maze
Button button(&LCDforScreenRefresh);
RNG_HandleTypeDef hrng = {0};

unsigned long Time = 0;
unsigned long TIMER_CHANGE_INTERVAL = 50000;
unsigned long millis();

int state = 0;

void setup()
{

    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(D8, INPUT_PULLUP);
    pinMode(USER_BTN, INPUT);
    maze.initializeRNG(&hrng);
    display.begin();
    Serial.begin(115200);
    Serial.println("Code has started");

    button.ball(display);
    // Forsiraj da kod misli da je partija igrice pobjeđena da bi se učitao novi random maze.
    //state = 1;
}

void loop()
{
    // unsigned long currentMillis = millis();
    //  Pozivanje metodi unutar klasa
    //  maze.drawLines(display, _m, _b1); //objekt.ime klase
    //  button.startButton(display);
    //  Serial.print(a);
    //button.startScreen(display);

    first();
    button.startScreen(display);
    

    screen.checkForRefresh();
}

void GameLoop()
{
    ball.updateBallposition(display);
    //ball.Time(display);
    ball.exitLine(display, maze.getCurrentMaze());
    if ((ball.checkColision(maze.getCurrentMaze())) != 0)
    {
        ball.newBallposition(display);
        // Serial.printf("Detection collision");
    }
}

void first()
{
    
    button.ballposition(display);
    display.display();
  
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