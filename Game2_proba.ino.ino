#include "Adafruit_GFX.h"
#include "ILI9341_STM32.h"
#include "defines.h"
#include "labirint.h"

#define TFT_DC 9
#define TFT_CS 10
Adafruit_ILI9341 display = Adafruit_ILI9341(TFT_CS, TFT_DC);

int x;
int SW = 2;
int SW_state = 0;
int z = 0;
bool ref = false;
bool time_game = false;

myline_t myline; // tip podatka
OBJECT_t OBJECT1;


// uint8_t myline = labirint[55][4];


void setup()
{
    // put your setup code here, to run once:
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);

    Serial.begin(115200);
    display.begin();
    display.setRotation(1);
    display.clearDisplay();
    display.setTextWrap(false);
    display.setTextSize(4);
    display.setTextColor(ILI9341_BLUE);
    start_game(OBJECT1, ILI9341_WHITE);
    display.display();
}

void loop()
{
    // put your main code here, to run repeatedly:
    int rawX = 1023 - analogRead(A0);
    int rawY = 1023 - analogRead(A1);

    int labSelect = random(0, 1); //Varijabla pomoću koje se ispisuje random labirint na zaslon

    drawLines(labs[labSelect], labElements[labSelect], ILI9341_WHITE); //ispis labirinta, dakle prvi argument je koji lab, drugi broj linija i treći boja
    drawCircle(OBJECT1, ILI9341_WHITE);

    if (rawX < 500 || rawX > 520)
    {
        OBJECT1.xOld = OBJECT1.x;
        OBJECT1.x += (511 - rawX) / 100;
        if (OBJECT1.x > 319)
            OBJECT1.x = 319;
        if (OBJECT1.x < 0)
            OBJECT1.x = 0;
        ref = true;
    }
    if (rawY < 500 || rawY > 520)
    {
        OBJECT1.yOld = OBJECT1.y;
        OBJECT1.y += (511 - rawY) / 100;

        if (OBJECT1.y > 239)
            OBJECT1.y = 239;
        if (OBJECT1.y < 0)
            OBJECT1.y = 0;
        ref = true;
    }
    if (ref == true)
    {
        ref = false;
        display.display();
    }
};

void drawLines(const myline_t *_m, int _bl, uint16_t _c)
{
    int col = 0;
    uint16_t color = ILI9341_WHITE;
    uint16_t color1 = ILI9341_RED;

    for (int i = 0; i < _bl; i++) // petlja za iscrtavanje svih linija u labirintu
    {
        display.drawLine(_m[i].x0, _m[i].y0, _m[i].x1, _m[i].y1, _c);
    };
}

void drawCircle(OBJECT_t _b, uint16_t _c)
{
    uint16_t color = ILI9341_WHITE;
    display.fillCircle(_b.x, _b.y, _b.r, ILI9341_WHITE);
}

void start_game(OBJECT_t _b, uint16_t _c) // poćetna pozicija kuglice kada se upali display
{
    OBJECT1.x = display.width() - 160;  //  početna pozicija kuglice po x osi
    OBJECT1.y = display.height() - 242; // početna pozicija kuglice po y osi
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
