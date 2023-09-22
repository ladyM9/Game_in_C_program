#include "Adafruit_GFX.h"
#include "ILI9341_STM32.h"
#include "SparkFunLSM6DS3.h"
#include "myDefines.h"
#include "pong.h"
#include "icons.h"
#include "screen.h"

Pong::Pong(void (*_callBack)())
{
    _colorpaddle = ILI9341_RED;

    requestForCallback = _callBack;
}

void Pong::paddle1(Adafruit_ILI9341 &lcd, myPaddle_t1 *p1)
{

    lcd.fillRect(p1->sx1, p1->sy1, p1->w, p1->h, _colorpaddle); // paddle korisnik

    updateScreenGame1();
}

void Pong::paddle2(Adafruit_ILI9341 &lcd, myPaddle_t2 *p2)
{

    lcd.fillRect(p2->sx2, p2->sy2, p2->w, p2->h, _colorpaddle); // paddle računalo
    updateScreenGame1();
}

void Pong::movePaddle1(Adafruit_ILI9341 &lcd, LSM6DS3 myIMU, myPaddle_t1 *p1) // paddle korisnik
{

    float rawX = myIMU.readFloatAccelX();
    float rawY = myIMU.readFloatAccelY();

    brzinax = rawX * -5;
    brzinay = rawY * -5;
    /*
        if (brzinax > 2)
            brzinax = 2;
        if (brzinay > 2)
            brzinay = 2;
        if (brzinax < -2)
            brzinax = -2;
        if (brzinay < -2)
            brzinay = -2;
    */

    Y0 = p1->sy1;

    /// kretanje prvog paddle, odnosno sa ovim paddle upravlja korisnik
    if (p1->sy1 <= 0)
    {
        p1->sy1 = 0;
    }

    if (p1->sy1 >= 190)
    {
        p1->sy1 = 190;
    }
    // xPOMAK1 += brzinax;

    p1->sy1 += brzinay;

    lcd.fillRect(p1->sx1, p1->sy1, p1->w, p1->h, _colorpaddle);

    updateScreenGame1();
}

void Pong::movePaddle2(Adafruit_ILI9341 &lcd, myPaddle_t2 *p2, my_ballPong *b)
{

    // kretanje drugog paddle odnosno sa ovim paddle upravlja računalo

    p2->sy2 = b->startBally - p2->h;

    if(p2->sy2 <= 0)
    {
        p2->sy2 = 0;
    }
    lcd.fillRect(p2->sx2, p2->sy2, p2->w, p2->h, _colorpaddle);

    updateScreenGame1();
}

void Pong::ball(Adafruit_ILI9341 &lcd, my_ballPong *b)
{

    lcd.fillCircle(b->startBallx, b->startBally, b->r, ILI9341_BLUE);
}

void Pong::moveBall(Adafruit_ILI9341 &lcd, my_ballPong *b)
{

    
    if (b->startBallx > lcd.width() || b->startBallx < 0)
    {

        ballDirectionX = -ballDirectionX;
    }
    if (b->startBally > lcd.height() || b->startBally < 0)
    {

        ballDirectionY = -ballDirectionY;
    }
    newxb = b->startBallx;
    newyb = b->startBally;
    b->startBallx += ballDirectionX;

    b->startBally += ballDirectionY;

    // if((ballX > p2->sx2) && (ballX < (p2->w + p2->sx2)) && (ballY > p2->sy2) && (ballY < (hp + p2->sy2)))//ako je unutar kvadrata

    lcd.fillCircle(b->startBallx, b->startBally, b->r, ILI9341_BLUE);
}

uint8_t Pong::checkCollisionPaddle(myPaddle_t1 *p1, myPaddle_t2 *p2, my_ballPong *b)
{
    uint8_t collision = 0;
    score = false;
    score2 = false;

    if (((b->startBallx - b->r) <= (p1->sx1 + p1->w)) && ((b->startBallx - b->r) > 0) && (b->startBally >= p1->sy1) && (b->startBally <= (b->startBally + p1->h)))
    {
        collision = 1;
        // Serial.println("KOLIZIJA!");
    }

    if (((b->startBallx + b->r) >= (p2->sx2)) && ((b->startBallx + b->r) > 0) && (b->startBally >= p2->sy2) && (b->startBally <= (b->startBally + p2->h)))
    {
        collision = 3;
    }

    if (((b->startBallx - b->r) <= 0) && ((b->startBally - b->r) <= 240) && (b->startBally >= 0))
    {
        score = true;
        collision = 2;
     

    }

    if (((b->startBallx + b->r) >= 320) && ((b->startBally + b->r) <= 240) && (b->startBally >= 0))
    {
        collision = 4;
        score2 = true;
 
    }

    return collision;
}

void Pong::newBallPosition(my_ballPong *b)
{
    ballDirectionX = -ballDirectionX;
    ballDirectionY = -ballDirectionY;
    b->startBallx = newxb;
    b->startBally = newyb;
    newxb += ballDirectionX;

    newyb += ballDirectionY;
}

void Pong::scoreInGame(Adafruit_ILI9341 &lcd)
{
    game_over = false;
    lcd.setCursor(10, 2);
    lcd.setTextSize(2);
    lcd.setTextColor(ILI9341_MAGENTA);
    
    
    lcd.printf("Live: %d", live);
    
    updateScreenGame1();
}
uint8_t Pong::live_User(Adafruit_ILI9341 &lcd)
{

    if (score == true)
    {
        lives_minus();
    }
    
    return live;
}

uint8_t Pong::lives_minus()
{
    live = live - 1;
    return live;
}

void Pong::scoreInGame2(Adafruit_ILI9341 &lcd) // racunanje scora za racunalo
{

    lcd.setCursor(190, 2);
    lcd.setTextSize(2);
    lcd.setTextColor(ILI9341_OLIVE);
    if (score2 == true && score3 == false)
    {
        live_rac -= 1;
    }
    score3 = score2;
    lcd.printf("Live_rac %d", live_rac);
    if (live_rac == 0)
    {
        game_over = true;
        live_rac = 5;
        
    }

    updateScreenGame1();
}

uint8_t Pong::GAME_OVER(Adafruit_ILI9341 &lcd)
{
    gm = false;
    if (live_User(lcd) == 0)
    {
        gm = true;
        live = 2;
    }
    return gm;
    gm = false;
}

void Pong::gameOverText(Adafruit_ILI9341 &lcd)
{

    lcd.setCursor(100, 50);
    lcd.setTextSize(3);
    lcd.setTextColor(ILI9341_CYAN);
    lcd.print("Game over");

    updateScreenGame1();
}
void Pong::updateScreenGame1()
{
    requestForCallback();
}
