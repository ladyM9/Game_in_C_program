#include "screen.h"
#include "ball.h"

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
        updateFlag = false;
    }
    
}
//void Screen::passCallbackToMe(Ball *ball, void (Ball::*updateBallposition)(Adafruit_ILI9341 &lcd, int _xCurrent, int _yCurrent))
//{
  //  (ball->*updateBallposition)(Adafruit_ILI9341 & l, int _xCurrent, int _yCurrent);
    //l->display();
//}
