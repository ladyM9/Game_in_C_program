#include "screen.h"
#include "ball.h"
#include "GUI.h"

static uint8_t updateFlag = false;  //zastavica pomoću koje određujem da li će se osvježiti zaslon

Screen::Screen(Adafruit_ILI9341 *lcd)
{
    _lcd= lcd;
}

void LCDforScreenRefresh()
{
    updateFlag = true;
}

void Screen::checkForRefresh()
{
    if(updateFlag == true ) //ako je zastavica true dogodit će se ispis na zaslon
    {
        _lcd->display();  //ispis na display
        _lcd->clearDisplay(); //brisanje sa display-a
        _lcd->setRotation(1); //rotacija display-a, mora se rotirat jer se inače ne vidi cijeli labirint na zaslonu
        updateFlag = false;
    }
    
}