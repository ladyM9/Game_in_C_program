#ifndef __BALL_H__
#define __BALL_H__

#include "ILI9341_STM32.h"
#include "maze.h"
#include "myDefines.h"


class Ball //klasa Ball nasljeđuje od klase Maze sve ono što je pod public
{
public:
    Ball(void (*_callBack)());
    // Ball(ToScreenfunc func); // konstruktor, mora biti public, defaultni konstruktor
    void updateScreen();
    void firstBallposition(Adafruit_ILI9341 &lcd, myMaze_t *_currentLab);
    void updateBallposition(Adafruit_ILI9341 &lcd); //funkcija pomoću koje se očitava pozicija kuglice koja se miče po displayu
    uint8_t checkColision(myMaze_t *_currentLab); //funkcija koja provjerava da li se dogodila kolizija između linije i kuglice
    uint8_t checkExit(myMaze_t *_currentLab); //funkcija koja provjerava da li je kuglica dotaknula liniju koja označava izlazak iz labirinta
    //void loadMaze(const myline_t *_ol, int *_br); //funkcija pomoću koje se učitava labirint u igricu
    void newBallposition(Adafruit_ILI9341 &lcd); //funkcija koja onemogućava da kuglica nakon što dotakne liniju da prijeđe preko te linije
    void exitLine(Adafruit_ILI9341 &lcd, myMaze_t *_currentLab); //funkcija za iscrtavanje izlazne linije
    uint8_t Time(Adafruit_ILI9341 &lcd); //funkcija za vrijeme u igrici
    

    private: // kad su varijable private tu im ne daješ vrijednost
    int X;
    int Y;
    int R;
    uint16_t _color;
    int xCurrent;
    int yCurrent;
    myline_t e;
    void (*requestForCallback)();
    void(*_l)();

    // ToScreenfunc func;
    // Zaslon*;
};

#endif
