#include "Adafruit_GFX.h"
#include "ILI9341_STM32.h"
#include "SparkFunLSM6DS3.h"
#include "myDefines.h"
#include "pong.h"
#include "icons.h"
#include "screen.h"

Pong::Pong(void (*_callBack)())
{
    _colorpaddle = ILI9341_RED;  //boja kuglice u igri

    requestForCallback = _callBack; //pokazivac callback funkcije
}

void Pong::paddle1(Adafruit_ILI9341 &lcd, myPaddle_t1 *p1)
{

    lcd.fillRect(p1->sx1, p1->sy1, p1->w, p1->h, _colorpaddle); // iscrtavanje reketa sa kojim upravlja korisnik

    updateScreenGame1();
}

void Pong::paddle2(Adafruit_ILI9341 &lcd, myPaddle_t2 *p2)
{

    lcd.fillRect(p2->sx2, p2->sy2, p2->w, p2->h, _colorpaddle); // iscrtavanje reketa sa kojim upravlja mikroupravljač
    updateScreenGame1();
}

void Pong::movePaddle1(Adafruit_ILI9341 &lcd, LSM6DS3 myIMU, myPaddle_t1 *p1) // kretanje reketa sa kojim upravlja korisnik
{

    float rawX = myIMU.readFloatAccelX(); //ocitavanje vrijednosti sa akcelerometra po x osi
    float rawY = myIMU.readFloatAccelY(); //ocitavanje vrijednosti sa akcelerometra po y osi

    brzinax = rawX * -5;  //brzini po x osi pridruzi ocitanu vrijednos sa akcelerometra pomnozenu sa -5 (-5 zbog smjera u kojem se krece)
    brzinay = rawY * -5;  //isto vrijedi i za y os

    Y0 = p1->sy1; 

    /// kretanje prvog paddle, odnosno sa ovim paddle upravlja korisnik
    if (p1->sy1 <= 0) //ako je pozicija reketa po y osi manja ili jednaka nuli pozicija reketa je jednaka 0
    {
        p1->sy1 = 0;
    }

    if (p1->sy1 >= 190) //ako je pozicija reketa po y osi veca ili jednaka 190, pocetna pozicija iscrtavanja reketa po y osi reketa je jednaka 190
    {
        p1->sy1 = 190;
    }
    // xPOMAK1 += brzinax;

    p1->sy1 += brzinay; //pozicija reketa se mijenja pomocu brzine odnosno nakretanjem akcelerometra

    lcd.fillRect(p1->sx1, p1->sy1, p1->w, p1->h, _colorpaddle);

    updateScreenGame1();
}

void Pong::movePaddle2(Adafruit_ILI9341 &lcd, myPaddle_t2 *p2, my_ballPong *b) //kretanje reketa sa kojim upravlja računalo
{
    p2->sy2 = b->startBally - p2->h;  //poziciji po y osi pridruzi trenutnu poziciju kuglice umanjenu za visinu reketa

    if(p2->sy2 <= 0) //ako je pozicija reketa jednaka ili manja od 0
    {
        p2->sy2 = 0; //pocetna pozicija iscrtavanja reketa po y osi je jednaka 10
    }
    lcd.fillRect(p2->sx2, p2->sy2, p2->w, p2->h, _colorpaddle);

    updateScreenGame1();
}

void Pong::ball(Adafruit_ILI9341 &lcd, my_ballPong *b) //metoda pomocu koje se iscrtava kuglica u igri
{

    lcd.fillCircle(b->startBallx, b->startBally, b->r, ILI9341_BLUE);
}

void Pong::moveBall(Adafruit_ILI9341 &lcd, my_ballPong *b) //metoda za kretanje kuflice u igri
{

    if (b->startBallx > lcd.width() || b->startBallx < 0) //ako je kuglica dotaknila gornji rub zaslona ili donji rub zaslona
    {

        ballDirectionX = -ballDirectionX; //promjeni smjer kretanja kuglice po x osi
    }
    if (b->startBally > lcd.height() || b->startBally < 0) //ako je kuglica dotaknila lijevi rub zaslona ili desni rub zaslona
    {

        ballDirectionY = -ballDirectionY; //promjeni smjer kuglice po y osi
    }
    newxb = b->startBallx; //novoj poziciji kuglice pridruzi trenutnu poziciju kuglice po x osi
    newyb = b->startBally; //novoj poziciji kuglice pridruzi trenutnu poziciju kuglice po y osi
    b->startBallx += ballDirectionX; //pozicija kuglice se mijenja s obzirom na trenutni smjer

    b->startBally += ballDirectionY;

    lcd.fillCircle(b->startBallx, b->startBally, b->r, ILI9341_BLUE);
}

uint8_t Pong::checkCollisionPaddle(myPaddle_t1 *p1, myPaddle_t2 *p2, my_ballPong *b) //metoda za ispitivanje kolizije izmedu reketa i kuglice
{
    uint8_t collision = 0; 
    score = false;
    score2 = false;


    //prvi uvjet ispituje da li je reket sa kojom upravlja korisnik, odnosno da li je trenutna pozicija kuglice po x osi, y osi i njen radijus
    //da li su dotaknuli trenutnu poziciju reketa po x osi i po y osi
    if (((b->startBallx - b->r) <= (p1->sx1 + p1->w)) && ((b->startBallx - b->r) > 0) && (b->startBally >= p1->sy1) && (b->startBally <= (b->startBally + p1->h)))
    {
        collision = 1;
    }

    //drugi uvjet ispituje da li je reket sa kojom upravlja mikroupravljač, odnosno da li je trenutna pozicija kuglice po x osi, y osi i njen radijus
    //da li su dotaknuli trenutnu poziciju reketa po x osi i po y osi
    if (((b->startBallx + b->r) >= (p2->sx2)) && ((b->startBallx + b->r) > 0) && (b->startBally >= p2->sy2) && (b->startBally <= (b->startBally + p2->h)))
    {
        collision = 3;
    }

    //uvjet koji ispituje da li je kuglica otisla iza reketa sa kojim upravlja korisnik
    if (((b->startBallx - b->r) <= 0) && ((b->startBally - b->r) <= 240) && (b->startBally >= 0))
    {
        score = true; //ako je uvjet ispunjen score stavi na true to znaci da je kuglica otisla iza reketa i dotaknila rub
        collision = 2;
     

    }

    //uvjet koji ispituje da li je kuglica otisla iza reketa sa kojim upravlja mikroupravljač
    if (((b->startBallx + b->r) >= 320) && ((b->startBally + b->r) <= 240) && (b->startBally >= 0))
    {
        collision = 4;
        score2 = true;  //ako je uvjet ispunjen score stavi na true to znaci da je kuglica otisla iza reketa i dotaknila rub
 
    }

    return collision;  //vrati zastavicu collision odnosno da li se kolizija dogodila i koja se kolizija dogodila
}

void Pong::newBallPosition(my_ballPong *b) //metoda za kretanje kuglice
{
    ballDirectionX = -ballDirectionX;
    ballDirectionY = -ballDirectionY;
    b->startBallx = newxb;
    b->startBally = newyb;
    newxb += ballDirectionX;

    newyb += ballDirectionY;
}

void Pong::scoreInGame(Adafruit_ILI9341 &lcd) //metoda za ispisivanje trentunog broja zivota za reket sa kojim upravlja korisnik u igrici
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

    if (score == true) //ako je zastavica score jednaka true odnosno ako je kuglica otisla iza reketa
    {
        lives_minus(); //pozovi funkciju za smanjivanje zivota
    }
    
    return live; //vrati broj zivota nakon pozvane funkcije za smanjivanje zivota
}

uint8_t Pong::lives_minus() //metoda za smanjivanje zivota reketa sa kojim upravlja korisnik
{
    live = live - 1; //trenutni broj zivota smanji za jedan
    return live;
}

void Pong::scoreInGame2(Adafruit_ILI9341 &lcd) // racunanje scora za racunalo
{

    lcd.setCursor(190, 2);
    lcd.setTextSize(2);
    lcd.setTextColor(ILI9341_OLIVE);
    if (score2 == true && score3 == false) //ako je zastavica za score2 jednaka istini odnosno ako je kuglica otisla 
    // iza reketa sa kojim upravlja racunalo
    {
        live_rac -= 1; // trenutni broj zivota za reket sa kojim upravlja racunalo smanji za 1
    }
    score3 = score2;
    lcd.printf("Live_rac %d", live_rac);
    if (live_rac == 0) //ako je broj zivota za reket sa kojim upravlja raunalo jednako 0
    {
        game_over = true; //zastavica game_over je jednaka true
        live_rac = 5; //broj zivota racunala stavi na pocetni broj zivota
        
    }

    updateScreenGame1();
}

void Pong::score_In_High_Score(Adafruit_ILI9341 &lcd) //metoda za ispisivanje osvojenih bodova tijekom igre 
{
    lcd.setCursor(75, 20);
    lcd.setTextSize(2);
    lcd.setTextColor(ILI9341_MAGENTA);
    lcd.printf("Score in game: ");
    lcd.setCursor(75, 50);
    lcd.setTextSize(2);
    lcd.setTextColor(ILI9341_MAGENTA);
    lcd.printf("Live: %d", live);
    lcd.setCursor(75, 80);
    lcd.setTextSize(2);
    lcd.setTextColor(ILI9341_MAGENTA);
    lcd.printf("Live_rac: %d", live_rac);
    
    updateScreenGame1();
}

uint8_t Pong::GAME_OVER(Adafruit_ILI9341 &lcd) // metoda koja ispituje da li je korisnik izgubio sve zivote
{ 
    gm = false; //zastavicu gm je prvo potrebno staviti na false odnosno laz
    if (live_User(lcd) == 0) //ako je broj zivota korisnika jednak 0
    {
        gm = true; //zastavica gm je jednaka istini
        live = 5; //broj zivota korisnika vrati na pocetni broj zivota
    }
    return gm; //vrati zastavicu
    gm = false; //ponisti zastavicu
}

void Pong::gameOverText(Adafruit_ILI9341 &lcd) //metoda za ispisivanje game over teksta
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