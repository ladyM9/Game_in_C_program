#include "zaslon.h"

static uint8_t updateFlag = false;

void LCDrequestForRefresh()
{
    updateFlag = true;
}

Zaslon::Zaslon(Adafruit_ILI9341 *lcd)
{
    _lcd = lcd;
}

void Zaslon::checkForRefresh()
{
    if (updateFlag == true)
    {
        _lcd->display();
        _lcd->clearDisplay();
        updateFlag = false;
    }
}