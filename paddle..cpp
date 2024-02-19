#include "Adafruit_GFX.h"
#include "ILI9341_STM32.h"
#include "SparkFunLSM6DS3.h"
#include "paddle.h"
#include "screen.h"

Pong::Pong(void (*_callBack)())
{
    _colorpaddle = ILI9341_RED;
    requestForCallback = _callBack;
}

void Pong::paddle(Adafruit_ILI9341 &lcd)
{

    // lcd.drawLine(2,20,2,50, _colorpaddle);
    lcd.fillRect(5, 5, 5, 30, _colorpaddle);
    lcd.fillRect(315,5,5,30, _colorpaddle);

    updateScreenGame1();
}
void Pong::drawPaddle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t _c)
{
    Xp1 = x0;
    Xp2 = x1;
    Yp1 = y0;
    Yp2 = y1;
    _c = _colorpaddle;
}
void Pong::movePaddle(Adafruit_ILI9341 &lcd, LSM6DS3 myIMU)
{
    float rawX = myIMU.readFloatAccelX();
    float rawY = myIMU.readFloatAccelY();
    X1 = 315;

    brzinax += rawX;
    brzinay += rawY;

    brzina2x += 0.5;
    brzina2y += 0.5;

    if (brzinax > 1)
        brzinax = 1;
    if (brzinay > 1)
        brzinay = 1;
    if (brzinax < -1)
        brzinax = -1;
    if (brzinay < -1)
        brzinay = -1;

    //X0 = xPOMAK1;
    Y0 = yPOMAK1;
    Y1 = yPOMAK2;

    xPOMAK1 += brzinax;
    yPOMAK1 += brzinay;

   

    if(Y0 <= 0) 
    {
        brzinay += 1;
    }

    if(Y0 >= 218)
    {
        brzinay -=1;
    }


    if( X1 == 315)
    {
     yPOMAK2 += brzina2y;

    }

    if((X1 == 315) && (yPOMAK2 >= 215))
    {
        yPOMAK2 -= brzina2y;
    }
    

    lcd.fillRect(X0, yPOMAK1, 5, 30, _colorpaddle);
    lcd.fillRect(X1, yPOMAK2, 5, 30, _colorpaddle);
    updateScreenGame1();

}
void Pong::updateScreenGame1()
{
    requestForCallback();
}