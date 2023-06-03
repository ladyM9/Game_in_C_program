#include "Adafruit_GFX.h"
#include "ILI9341_STM32.h"
#include "ball.h"
#include "screen.h"
#include "maze.h"
#include "lab.h"
#include "hal_conf_extra.h"
RNG_HandleTypeDef hrng = {0};

unsigned long previousMillis = 0;
unsigned long intervalOn = 5000;  // use 3000 for three seconds on
unsigned long intervalOff = 5000; // use 3600000 for one hour off
unsigned long interval = intervalOff;
unsigned long millis();

// #include "GUI.h"
#define TFT_DC 9
#define TFT_CS 10
Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC);

Screen screen(&display);         // objekt klase Screen
Ball ball(&LCDforScreenRefresh); // objekt klase Ball
Maze maze;                       // objekt klase Maze
// Button button;

// myline_t polje[80] = {{2.798259482601822, 3.2297342251706107, 137.11471464748928, 3.2297342251706107}, {159.50079050830385, 3.2297342251706107, 316.20332153400585, 3.2297342251706107}, {114.7286387866747, 29.0676080265355, 137.11471464748928, 29.0676080265355}, {181.88686636911842, 29.0676080265355, 226.65901809074757, 29.0676080265355}, {47.57041120423097, 54.90548182790039, 159.50079050830385, 54.90548182790039}, {204.272942229933, 54.90548182790039, 249.04509395156214, 54.90548182790039}, {25.184335343416397, 80.74335562926527, 47.57041120423097, 80.74335562926527}, {69.95648706504555, 80.74335562926527, 92.34256292586012, 80.74335562926527}, {114.7286387866747, 80.74335562926527, 204.272942229933, 80.74335562926527}, {249.04509395156214, 80.74335562926527, 271.4311698123767, 80.74335562926527}, {25.184335343416397, 106.58122943063016, 47.57041120423097, 106.58122943063016}, {69.95648706504555, 106.58122943063016, 92.34256292586012, 106.58122943063016}, {114.7286387866747, 106.58122943063016, 181.88686636911842, 106.58122943063016}, {204.272942229933, 106.58122943063016, 249.04509395156214, 106.58122943063016}, {271.4311698123767, 106.58122943063016, 293.8172456731913, 106.58122943063016}, {2.798259482601822, 132.41910323199505, 25.184335343416397, 132.41910323199505}, {92.34256292586012, 132.41910323199505, 114.7286387866747, 132.41910323199505}, {159.50079050830385, 132.41910323199505, 204.272942229933, 132.41910323199505}, {25.184335343416397, 158.25697703335993, 92.34256292586012, 158.25697703335993}, {114.7286387866747, 158.25697703335993, 137.11471464748928, 158.25697703335993}, {204.272942229933, 158.25697703335993, 271.4311698123767, 158.25697703335993}, {293.8172456731913, 158.25697703335993, 316.20332153400585, 158.25697703335993}, {47.57041120423097, 184.0948508347248, 69.95648706504555, 184.0948508347248}, {92.34256292586012, 184.0948508347248, 114.7286387866747, 184.0948508347248}, {137.11471464748928, 184.0948508347248, 159.50079050830385, 184.0948508347248}, {181.88686636911842, 184.0948508347248, 226.65901809074757, 184.0948508347248}, {249.04509395156214, 184.0948508347248, 316.20332153400585, 184.0948508347248}, {25.184335343416397, 209.93272463608972, 47.57041120423097, 209.93272463608972}, {69.95648706504555, 209.93272463608972, 181.88686636911842, 209.93272463608972}, {226.65901809074757, 209.93272463608972, 249.04509395156214, 209.93272463608972}, {271.4311698123767, 209.93272463608972, 293.8172456731913, 209.93272463608972}, {2.798259482601822, 235.7705984374546, 159.50079050830385, 235.7705984374546}, {181.88686636911842, 235.7705984374546, 316.20332153400585, 235.7705984374546}, {2.798259482601822, 3.2297342251706107, 2.798259482601822, 235.7705984374546}, {25.184335343416397, 3.2297342251706107, 25.184335343416397, 80.74335562926527}, {25.184335343416397, 158.25697703335993, 25.184335343416397, 209.93272463608972}, {47.57041120423097, 29.0676080265355, 47.57041120423097, 54.90548182790039}, {47.57041120423097, 80.74335562926527, 47.57041120423097, 132.41910323199505}, {47.57041120423097, 209.93272463608972, 47.57041120423097, 235.7705984374546}, {69.95648706504555, 3.2297342251706107, 69.95648706504555, 29.0676080265355}, {69.95648706504555, 54.90548182790039, 69.95648706504555, 80.74335562926527}, {69.95648706504555, 106.58122943063016, 69.95648706504555, 158.25697703335993}, {69.95648706504555, 184.0948508347248, 69.95648706504555, 209.93272463608972}, {92.34256292586012, 29.0676080265355, 92.34256292586012, 54.90548182790039}, {92.34256292586012, 158.25697703335993, 92.34256292586012, 184.0948508347248}, {114.7286387866747, 3.2297342251706107, 114.7286387866747, 29.0676080265355}, {114.7286387866747, 106.58122943063016, 114.7286387866747, 132.41910323199505}, {114.7286387866747, 158.25697703335993, 114.7286387866747, 184.0948508347248}, {137.11471464748928, 106.58122943063016, 137.11471464748928, 158.25697703335993}, {137.11471464748928, 184.0948508347248, 137.11471464748928, 209.93272463608972}, {159.50079050830385, 3.2297342251706107, 159.50079050830385, 54.90548182790039}, {159.50079050830385, 132.41910323199505, 159.50079050830385, 184.0948508347248}, {181.88686636911842, 29.0676080265355, 181.88686636911842, 54.90548182790039}, {181.88686636911842, 132.41910323199505, 181.88686636911842, 158.25697703335993}, {181.88686636911842, 184.0948508347248, 181.88686636911842, 235.7705984374546}, {204.272942229933, 54.90548182790039, 204.272942229933, 106.58122943063016}, {204.272942229933, 158.25697703335993, 204.272942229933, 184.0948508347248}, {204.272942229933, 209.93272463608972, 204.272942229933, 235.7705984374546}, {226.65901809074757, 3.2297342251706107, 226.65901809074757, 29.0676080265355}, {226.65901809074757, 54.90548182790039, 226.65901809074757, 80.74335562926527}, {226.65901809074757, 132.41910323199505, 226.65901809074757, 158.25697703335993}, {249.04509395156214, 29.0676080265355, 249.04509395156214, 54.90548182790039}, {249.04509395156214, 80.74335562926527, 249.04509395156214, 132.41910323199505}, {249.04509395156214, 184.0948508347248, 249.04509395156214, 209.93272463608972}, {271.4311698123767, 3.2297342251706107, 271.4311698123767, 80.74335562926527}, {271.4311698123767, 106.58122943063016, 271.4311698123767, 158.25697703335993}, {271.4311698123767, 209.93272463608972, 271.4311698123767, 235.7705984374546}, {293.8172456731913, 29.0676080265355, 293.8172456731913, 132.41910323199505}, {316.20332153400585, 3.2297342251706107, 316.20332153400585, 235.7705984374546}};

void setup()
{

    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(D6, INPUT);
    pinMode(USER_BTN, INPUT_PULLDOWN);
    display.begin();
    Serial.begin(115200);
    Serial.println("Code has started");

    initializeRNG(&hrng);
}
bool oldState = HIGH;

void loop()
{
    unsigned long currentMillis = millis();
    // Pozivanje metodi unutar klasa
    // maze.drawLines(display, _m, _b1); //objekt.ime klase
    // button.startButton(display);
    // Serial.print(a);

    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;
        if (ball.Time(display) == true)
        {
            display.clearDisplay();
            int r = getNumber(&hrng, 0, 5);
            maze.drawLines(display, labirint[r], labElements);
            GameLoop();
            interval = intervalOn;
        }

        else
        {
            maze.drawLines(display, lab1, labElements);
            GameLoop();
            interval = intervalOff;
        }
    }

    // Get the button state.

    // If the button is pressed, generate new random number.

    screen.checkForRefresh();
}

void GameLoop()
{
    ball.updateBallposition(display);
    ball.exitLine(display, exitLine, labExitEl);
    ball.Time(display);
    if ((ball.checkColision(labirint[0], labElements)) != 0)
    {
        ball.newBallposition(display);
        // Serial.printf("Detection collision");
    }
    if ((ball.checkExit(exitLine, labElements)) == true)
    {
        display.clearDisplay();
        Serial.printf("Exit, congrats");
    }
}
void initializeRNG(RNG_HandleTypeDef *_hrng)
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

int getNumber(RNG_HandleTypeDef *_hrng, int min, int max)
{
    uint32_t randomNumber;
    HAL_RNG_GenerateRandomNumber(_hrng, &randomNumber);

    int myRandom = (int)((double)(randomNumber) / (double)(UINT32_MAX) * (abs(min - max))) - min;

    return myRandom;
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