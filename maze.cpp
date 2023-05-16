#include "maze.h"
#include "ball.h"
#include "screen.h"

Maze::Maze()
{
    color1 = ILI9341_ORANGE;
    X0;
    Y0;
    X1;
    Y1;
    //b = 80;
}


void Maze::drawLines(Adafruit_ILI9341 &lcd, const myline_t *_m, int *_bl)
{
   
    b = _bl;
    m = _m;
   // Ball::updateBallposition(a,c);

   // obj.updateBallposition(a,c);
   // myline_t polje[120] = {{2.798259482601822, 3.2297342251706107, 137.11471464748928, 3.2297342251706107}, {159.50079050830385, 3.2297342251706107, 316.20332153400585, 3.2297342251706107}, {114.7286387866747, 29.0676080265355, 137.11471464748928, 29.0676080265355}, {181.88686636911842, 29.0676080265355, 226.65901809074757, 29.0676080265355}, {47.57041120423097, 54.90548182790039, 159.50079050830385, 54.90548182790039}, {204.272942229933, 54.90548182790039, 249.04509395156214, 54.90548182790039}, {25.184335343416397, 80.74335562926527, 47.57041120423097, 80.74335562926527}, {69.95648706504555, 80.74335562926527, 92.34256292586012, 80.74335562926527}, {114.7286387866747, 80.74335562926527, 204.272942229933, 80.74335562926527}, {249.04509395156214, 80.74335562926527, 271.4311698123767, 80.74335562926527}, {25.184335343416397, 106.58122943063016, 47.57041120423097, 106.58122943063016}, {69.95648706504555, 106.58122943063016, 92.34256292586012, 106.58122943063016}, {114.7286387866747, 106.58122943063016, 181.88686636911842, 106.58122943063016}, {204.272942229933, 106.58122943063016, 249.04509395156214, 106.58122943063016}, {271.4311698123767, 106.58122943063016, 293.8172456731913, 106.58122943063016}, {2.798259482601822, 132.41910323199505, 25.184335343416397, 132.41910323199505}, {92.34256292586012, 132.41910323199505, 114.7286387866747, 132.41910323199505}, {159.50079050830385, 132.41910323199505, 204.272942229933, 132.41910323199505}, {25.184335343416397, 158.25697703335993, 92.34256292586012, 158.25697703335993}, {114.7286387866747, 158.25697703335993, 137.11471464748928, 158.25697703335993}, {204.272942229933, 158.25697703335993, 271.4311698123767, 158.25697703335993}, {293.8172456731913, 158.25697703335993, 316.20332153400585, 158.25697703335993}, {47.57041120423097, 184.0948508347248, 69.95648706504555, 184.0948508347248}, {92.34256292586012, 184.0948508347248, 114.7286387866747, 184.0948508347248}, {137.11471464748928, 184.0948508347248, 159.50079050830385, 184.0948508347248}, {181.88686636911842, 184.0948508347248, 226.65901809074757, 184.0948508347248}, {249.04509395156214, 184.0948508347248, 316.20332153400585, 184.0948508347248}, {25.184335343416397, 209.93272463608972, 47.57041120423097, 209.93272463608972}, {69.95648706504555, 209.93272463608972, 181.88686636911842, 209.93272463608972}, {226.65901809074757, 209.93272463608972, 249.04509395156214, 209.93272463608972}, {271.4311698123767, 209.93272463608972, 293.8172456731913, 209.93272463608972}, {2.798259482601822, 235.7705984374546, 159.50079050830385, 235.7705984374546}, {181.88686636911842, 235.7705984374546, 316.20332153400585, 235.7705984374546}, {2.798259482601822, 3.2297342251706107, 2.798259482601822, 235.7705984374546}, {25.184335343416397, 3.2297342251706107, 25.184335343416397, 80.74335562926527}, {25.184335343416397, 158.25697703335993, 25.184335343416397, 209.93272463608972}, {47.57041120423097, 29.0676080265355, 47.57041120423097, 54.90548182790039}, {47.57041120423097, 80.74335562926527, 47.57041120423097, 132.41910323199505}, {47.57041120423097, 209.93272463608972, 47.57041120423097, 235.7705984374546}, {69.95648706504555, 3.2297342251706107, 69.95648706504555, 29.0676080265355}, {69.95648706504555, 54.90548182790039, 69.95648706504555, 80.74335562926527}, {69.95648706504555, 106.58122943063016, 69.95648706504555, 158.25697703335993}, {69.95648706504555, 184.0948508347248, 69.95648706504555, 209.93272463608972}, {92.34256292586012, 29.0676080265355, 92.34256292586012, 54.90548182790039}, {92.34256292586012, 158.25697703335993, 92.34256292586012, 184.0948508347248}, {114.7286387866747, 3.2297342251706107, 114.7286387866747, 29.0676080265355}, {114.7286387866747, 106.58122943063016, 114.7286387866747, 132.41910323199505}, {114.7286387866747, 158.25697703335993, 114.7286387866747, 184.0948508347248}, {137.11471464748928, 106.58122943063016, 137.11471464748928, 158.25697703335993}, {137.11471464748928, 184.0948508347248, 137.11471464748928, 209.93272463608972}, {159.50079050830385, 3.2297342251706107, 159.50079050830385, 54.90548182790039}, {159.50079050830385, 132.41910323199505, 159.50079050830385, 184.0948508347248}, {181.88686636911842, 29.0676080265355, 181.88686636911842, 54.90548182790039}, {181.88686636911842, 132.41910323199505, 181.88686636911842, 158.25697703335993}, {181.88686636911842, 184.0948508347248, 181.88686636911842, 235.7705984374546}, {204.272942229933, 54.90548182790039, 204.272942229933, 106.58122943063016}, {204.272942229933, 158.25697703335993, 204.272942229933, 184.0948508347248}, {204.272942229933, 209.93272463608972, 204.272942229933, 235.7705984374546}, {226.65901809074757, 3.2297342251706107, 226.65901809074757, 29.0676080265355}, {226.65901809074757, 54.90548182790039, 226.65901809074757, 80.74335562926527}, {226.65901809074757, 132.41910323199505, 226.65901809074757, 158.25697703335993}, {249.04509395156214, 29.0676080265355, 249.04509395156214, 54.90548182790039}, {249.04509395156214, 80.74335562926527, 249.04509395156214, 132.41910323199505}, {249.04509395156214, 184.0948508347248, 249.04509395156214, 209.93272463608972}, {271.4311698123767, 3.2297342251706107, 271.4311698123767, 80.74335562926527}, {271.4311698123767, 106.58122943063016, 271.4311698123767, 158.25697703335993}, {271.4311698123767, 209.93272463608972, 271.4311698123767, 235.7705984374546}, {293.8172456731913, 29.0676080265355, 293.8172456731913, 132.41910323199505}, {316.20332153400585, 3.2297342251706107, 316.20332153400585, 235.7705984374546}};
     // pokazivač pokazuje na polje
    for (int i = 0; i < b[0] ; i++)
    {
        lcd.drawLine(m[i].x0, m[i].y0, m[i].x1, m[i].y1, color1); // ovako ako ne napišeš labirint ti se neće prikazati na zaslonu!!!!!
    }
    
}

void Maze::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t _c)
{
    X0 = x0;
    Y0 = y0;
    X1 = x1;
    Y1 = y1;
    color1 = _c;
}