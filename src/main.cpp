#include <Arduino.h>
#include "SnowingGame.h"

#define LCD_ROWS 2
#define LCD_COLS 16
#define BUTTON 4

SnowingGame game(LCD_COLS, LCD_ROWS, BUTTON);

void setup()
{
  game.Init();
}

void loop()
{
  game.Tick();
  delay(500);
}