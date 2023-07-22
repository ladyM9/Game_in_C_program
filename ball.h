#ifndef __BALL_H__
#define __BALL_H__

#include "ILI9341_STM32.h"
#include "maze.h"
#include "myDefines.h"


class Ball //klasa Ball nasljeÄ‘uje od klase Maze sve ono Ĺˇto je pod public
{
public:
    Ball(void (*_callBack)());
    // Ball(ToScreenfunc func); // konstruktor, mora biti public, defaultni konstruktor
    void updateScreen();
    void firstBallposition(Adafruit_ILI9341 &lcd, myMaze_t *_currentLab);
    void updateBallposition(Adafruit_ILI9341 &lcd); //funkcija pomoÄ‡u koje se oÄŤitava pozicija kuglice koja se miÄŤe po displayu
    uint8_t checkColision(myMaze_t *_currentLab); //funkcija koja provjerava da li se dogodila kolizija izmeÄ‘u linije i kuglice
    uint8_t checkExit(myMaze_t *_currentLab); //funkcija koja provjerava da li je kuglica dotaknula liniju koja oznaÄŤava izlazak iz labirinta
    //void loadMaze(const myline_t *_ol, int *_br); //funkcija pomoÄ‡u koje se uÄŤitava labirint u igricu
    void newBallposition(Adafruit_ILI9341 &lcd); //funkcija koja onemoguÄ‡ava da kuglica nakon Ĺˇto dotakne liniju da prijeÄ‘e preko te linije
    void exitLine(Adafruit_ILI9341 &lcd, myMaze_t *_currentLab); //funkcija za iscrtavanje izlazne linije
    void Time(Adafruit_ILI9341 &lcd, unsigned long A); //funkcija za vrijeme u igrici
    void Score(Adafruit_ILI9341 &lcd);
    void score_Game(Adafruit_ILI9341 &lcd);
    

    private: // kad su varijable private tu im ne dajeĹˇ vrijednost
    int X;
    int Y;
    float R;
    uint16_t _color;
    uint8_t score = false;
    uint8_t game_ov = false;
    uint8_t scoreOld = score;
    uint8_t live = 3;
    uint8_t bodovi = 10; //tu moras postaviti pocetni broj bodova u igrici jer inace ti se bodovi nece ispisivati jer svaki put kad
    //kod ude u igricu u metodu za score bodove postavi na 100 i onda se nece smanjivati bodovi u igrici
    int xCurrent;
    int yCurrent;
    myline_t e;
    void (*requestForCallback)();

};

#endif