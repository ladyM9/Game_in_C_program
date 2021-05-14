#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
const int cellSize = 2;
const int w = 74;
const int h = 36;
int lab[w * h];
int dx[] = { -1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};
void setup() {
  // put your setup code here, to run once:
  //  pinMode(D2, INPUT_PULLUP);
  Serial.begin(9600);
  display.begin();
  display.clearDisplay();
  display.setTextWrap(false);
  display.setContrast(50);
  display.setCursor(0, 0);
  display.setTextColor(BLACK);
  prikazilab(lab, w, h);
  generiranjelab(lab, w, h);
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void prikazilab(const int *lab, int width, int height) {
  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
      if (lab[x + y * width] == 1)
        for (int i = 0; i < 4; i++)
        {
          int xx = x + dx[i];
          int yy = y + dy[i];
          if (0 <= xx && xx < w && 0 <= yy && yy < h && lab[yy * width + xx] == 1)
            display.drawLine(1 + x * cellSize + cellSize / 1, 1 + y * cellSize + cellSize / 1,
                             1 + x * cellSize + cellSize / 1 + (dx[i] * cellSize / 1),
                             1 + y * cellSize + cellSize / 2 + (dy[i] * cellSize / 1), BLACK);
        }
  display.display();
}

void generiranjelab(int *lab, int width, int height) {
  int x, y;
  for (x = 0; x < width * height; x++)
  {
    lab[x] = 1;
  }
  lab[1 * width + 1] = 0;

  // Seed the random number generator.
  // srand(time(0));
  for (y = 1; y < height; y += 2)
  {
    for (x = 1; x < width; x += 2)
    {
      carveMaze(lab, width, height, x, y);
    }
  }

  // Set up the entry and exit.
  lab[0 * width + 1] = 0;
  lab[(height - 1) * width + (width - 2)] = 0;
}
void carveMaze(int *lab, int width, int height, int x, int y)
{
  int x1, y1;
  int x2, y2;
  int dx, dy;
  int dir, count;

  dir = random(4);
  count = 0;
  while (count < 4)
  {
    dx = 0;
    dy = 0;
    switch (dir)
    {
      case 0:
        dx = 1;
        break;
      case 1:
        dy = 1;
        break;
      case 2:
        dx = -1;
        break;
      default:
        dy = -1;
        break;
    }
    x1 = x + dx;
    y1 = y + dy;
    x2 = x1 + dx;
    y2 = y1 + dy;
    if (x2 > 0 && x2 < width && y2 > 0 && y2 < height && lab[y1 * width + x1] == 1 && lab[y2 * width + x2] == 1)
    {
      lab[y1 * width + x1] = 0;
      lab[y2 * width + x2] = 0;
      x = x2;
      y = y2;
      dir = random(4);
      count = 0;
    }
    else
    {
      dir = (dir + 1) % 4;
      count += 1;
    }
  }
}
