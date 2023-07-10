#include "GUI.h"
#include "screen.h"

Button::Button(void(*_call)())
{
    request = _call;
}

void Button::startScreen(Adafruit_ILI9341 &lcd)
{
    X = 1;
    Y = 1;
    W = 50;
    H = 50;
    r = 2;
    
    //lcd.fillRect(1,1,120,120, ILI9341_GREEN);
    lcd.fillRoundRect(X,Y,W,H, r, ILI9341_GREEN);
    lcd.setRotation(1);
    lcd.setTextWrap(1);
    lcd.setTextSize(3);
    lcd.setTextColor(ILI9341_BLUE);
    lcd.setCursor(15,15);
    lcd.println("Easy");
    
    lcd.display();
}

void Button::drawRectangle(int16_t x, int16_t y, int16_t w, int16_t h )
{
    X = x;
    Y = y;
    W = w;
    H = h;

}

void Button::ball(Adafruit_ILI9341 &lcd)
{
    xp = 20;
    yp = 20;
    rp = 2;
    lcd.fillCircle(xp, yp, rp, ILI9341_BLUE);
    
    
}

void Button::updateFirstScreen()
{
    request;
}

void Button::ballposition(Adafruit_ILI9341 &lcd)
{

    int rawX = 1023 - analogRead(A0);
    int rawY = 1023 - analogRead(A1);
    int pushH;
    int pushL;
    xc = xp;
    yc = yp;
    xp += (511 - rawX) / 100;
    yp += (511 - rawY) / 100;
    pushH != digitalRead(D8);
    pushL = digitalRead(D8);

    if(digitalRead(D8) == pushH)
    {
        Serial.print("Push");
    }


    

    lcd.fillCircle(xp, yp, rp, ILI9341_BLUE); // ispisivanje kuglice na poetnoj poziciji, tu mora pisat ovo( NEPREMJEĹ TAJ INAÄ†E SE NEÄ†E ISPISAT NA DISPLAY)
    updateFirstScreen();
}

void Button::newposition(Adafruit_ILI9341 &lcd)
{
    xp = xc;
    yp = yc;
}


