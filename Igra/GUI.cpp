#include "GUI.h"
#include "screen.h"

Button::Button(void (*_call)())
{
    request = _call;
}

int Button::myButton(Adafruit_ILI9341 &lcd, int _xcur, int _ycur, int x, int y, int w, int h, int _textscale, char *mytext, int draw) //metoda pomocu koje ispisujem pojedinu tipku na display
{
    int push_button = 0; // varijabla koja govori da li je moja tipka pritisnuta ili nije, u prvom trenutku nije pritisnuta

    int _color = ILI9341_BLACK; // Boja teksta tipke

    int pushb = digitalRead(D8); // ocitavanje digitalne vrijednosti sa push tipke(SW) na joysticku

    if ((xp > x) && (xp < (w + x)) && (yp > y) && (yp < (h + y)) && (pushb == false)) // ako je kursor postavljen na tipku i ako je pushb pritisnut
        push_button = 1;                                                              // push_button je false odnosno tipka na displayu je pritisnuta

    if (draw) // varijabla draw označava to da li će se tipka prikazati na display-u ili ne, dakle ako je istina onda će se prikazati
    {
        // TEXT ti je polje tipa char, znaci trebas imati pokazivac na to polje
        int duljinatexta = strlen(mytext) * 6 * _textscale;
        int xpos = (w / 2) + x - (duljinatexta / 2);
        int ypos = (h / 2) + y - (_textscale * 8 / 2);

        lcd.fillRoundRect(x, y, w, h, 2, ILI9341_PURPLE);
        lcd.drawRoundRect(x - 1, y - 1, w + 2, h, 2, ILI9341_NAVY);
        lcd.setTextColor(_color);
        lcd.setTextSize(_textscale);
        lcd.setCursor(xpos, ypos);
        lcd.print(mytext);
    }

    return push_button;
}
int Button::back_Button(Adafruit_ILI9341 &lcd, int x, int y, int h, int w, int _textscale, char *mytext, int draw)
{

    int push_back = 0;
    int _color = ILI9341_WHITE; // Boja teksta tipke

    int pushback = digitalRead(D4); // ocitavanje digitalne vrijednosti sa push tipke(SW) na joysticku

    if (pushback == false) // ako je kursor postavljen na tipku i ako je pushb pritisnut
        push_back = 1;                                                              // push_button je false odnosno tipka na displayu je pritisnuta

    if (draw) // varijabla draw označava to da li će se tipka prikazati na display-u ili ne, dakle ako je istina onda će se prikazati
    {
        // TEXT ti je polje tipa char, znaci trebas imati pokazivac na to polje
        int duljinatexta = strlen(mytext) * 6 * _textscale;
        int xpos = (w / 2) + x - (duljinatexta / 2);
        int ypos = (h / 2) + y - (_textscale * 8 / 2);

        lcd.fillRoundRect(x, y, w, h, 2, ILI9341_PURPLE);
        lcd.drawRoundRect(x - 1, y - 1, w + 2, h, 2, ILI9341_NAVY);
        lcd.setTextColor(_color);
        lcd.setTextSize(_textscale);
        lcd.setCursor(xpos, ypos);
        lcd.print(mytext);
    }

    return push_back;
}

void Button::cursor(Adafruit_ILI9341 &lcd, int draw_cursor) // metoda pomocu koje se pomice i ispisuje kursor u prozoru za odabir tezine igrice na display
{
    Serial.begin(115200);
    int x1 = 0;
    int x2 = 319;
    int y1 = 0;
    int y2 = 239;
    int width1 = abs(x1 - x2); //racunanje sirine kursora
    int he = abs(y1 - y2); //racunanje visine kursora
    if (draw_cursor) // ako je zastavica draw_cursor postavljena na true( sto znaci da se se kursor ispisati na zaslon)
    {
        int rawX = 1023 - analogRead(A0); //- analogRead(A0); // ocitavaj x os
        int rawY = 1023 - analogRead(A1); // ocitavaj y os
        xp -= (511 - rawX) / 100;
        yp -= (511 - rawY) / 100;

        if ((xp > x1) && (xp < (width1 + x1)) && (yp < y1)) 
        {
            xp = 150;
            yp = 150;
        }
        if ((yp > y1) && (yp < (he + y1)) && (xp < 0))
        {
            xp = 150;
            yp = 150;
        }
        if ((xp > x1) && (xp < (width1 + x1)) && (yp > y2))
        {
            xp = 150;
            yp = 150;
           
        }
        if ((yp > y1) && (yp < (he + y1)) && (xp > x2))
        {
            xp = 150;
            yp = 150;
           
        }

        updateFirstScreen();                                                  // updetaj screen odnosno konstatno ispisuj kursor na novoj poziciji a brisi na staroj
        lcd.fillTriangle(xp, yp, xp + 20, yp - 5, xp, yp + 10, ILI9341_BLUE); // iscrtavanje kursora na display( nas kursor je u obliku trokuta)
    }
}

void Button::updateFirstScreen() // metoda pomocu koje pozivam metodu za request odnosno refresh zaslona
{
    request();
}
