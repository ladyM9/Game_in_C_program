#ifndef __BALL_H__
#define __BALL_H__

#include "ILI9341_STM32.h"
#include "maze.h"
#include "myDefines.h"
#include "SparkFunLSM6DS3.h"

class Ball
{
public:
    Ball(void (*_callBack)());
    // Ball(ToScreenfunc func); // konstruktor, mora biti public, defaultni konstruktor
    void updateScreen();  //funkcija pomocu koje se nesto ispisuje na display, pomocu koje se celara desplay
    void firstBallposition(Adafruit_ILI9341 &lcd, myMaze_t *_currentLab); //pocetna pozicija kuglice u labirintu, odnosno kuglica je smjestena na pocetak labirinta
    void updateBallposition(Adafruit_ILI9341 &lcd, LSM6DS3 myIMU); // funkcija pomocu koje se ocitava pozicija kuglice koja se krece po displayu pomocu akceleometra
    uint8_t checkColision(Adafruit_ILI9341 &lcd,myMaze_t *_currentLab);                  // funkcija koja provjerava da li se dogodila kolizija izmedu linije u labirintu i kuglice
    uint8_t checkExit(Adafruit_ILI9341 &lcd,myMaze_t *_currentLab);                      // funkcija koja provjerava da li je kuglica dotaknula liniju koja oznacava izlazak iz labirinta
    // void loadMaze(const myline_t *_ol, int *_br); //funkcija pomoÄ‡u koje se uÄŤitava labirint u igricu
    void newBallposition(Adafruit_ILI9341 &lcd);                 // funkcija koja onemogucava da kuglica nakon sto dotakne liniju u labirintu ne prijede preko te linije 
    void exitLine(Adafruit_ILI9341 &lcd, myMaze_t *_currentLab); // funkcija za iscrtavanje izlazne linije
    void Time(Adafruit_ILI9341 &lcd, unsigned long time_game);           // funkcija za vrijeme u igrici
    uint8_t Score(Adafruit_ILI9341 &lcd);                          //funkcija pomocu koje se ispisuje score u igrici i u kojoj se provjerava da li treba smanjiti bodove u igrici ili ne
    void score_Game(Adafruit_ILI9341 &lcd);                     //funkcija koja se ispisuje nakon sto igrac prode kroz sve levele, odnosno ona pokazuje koliko korisnik ima jos zivota i koliko je skupio bodova
    void ukupni_Bodovi(Adafruit_ILI9341 &lcd);                  
    void win_Screen(Adafruit_ILI9341 &lcd);                     //funkcija koja se ispisuje ako je korisnik usojesno prosao kroz labirint          
    void game_Over(Adafruit_ILI9341 &lcd);
    void bod(Adafruit_ILI9341 &lcd, int draw, int Xb, int Yb);  //funkcija koja ispisuje slicicu koja oznacava dodatne bodove u igrici koje igrac moze skupiti
    int collision_bod(int xc, int yc);                           //funkcija koja provjerava da li je igrac dodtaknio slicicu za bodove
    int Live(Adafruit_ILI9341 &lcd);
    int no_l(Adafruit_ILI9341 &lcd);
    uint8_t GM(Adafruit_ILI9341 &lcd);
    uint8_t GM_SCORE(Adafruit_ILI9341 &lcd);
    void Bodovi_igra();
    void picture(Adafruit_ILI9341 &lcd);


private: // kad su varijable private tu im ne dajeĹˇ vrijednost
    float X, velX;
    float Y, velY;
    float xCurrent;
    float yCurrent;
    float R;
    int Xb, Yb;
    uint16_t _color;
    uint8_t score = false;
    uint8_t game_ov = false;
    uint8_t scoreOld = score;
    uint8_t g = false;
    int live = 3;
    int live_new = 3;
    uint8_t bodovi = 50; // tu moras postaviti pocetni broj bodova u igrici jer inace ti se bodovi nece ispisivati jer svaki put kad
    // kod ude u igricu u metodu za score bodove postavi na 100 i onda se nece smanjivati bodovi u igrici
    uint8_t bodovi_igra = 0;
    

    myline_t e;
    void (*requestForCallback)();
};

#endif