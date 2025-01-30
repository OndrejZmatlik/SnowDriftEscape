#include <Arduino.h>
#include "SnowingGame.h"

#define SNOWFLAKE_SYMBOL 0x01
#define PLAYER_SYMBOL 0x02

void SnowingGame::ClearGrid(void)
{
    for (int row = 0; row < rows; row++)
        for (int col = 0; col < cols; col++)
            grid[col][row] = 0x00;
}

void SnowingGame::DrawGrid(void)
{
    lcd.clear();
    for (int row = 0; row < rows; row++)
        for (int col = 0; col < cols; col++)
        {
            if (grid[col][row] == 0x00)
                continue;

            lcd.setCursor(row, col);
            if (grid[col][row] == SNOWFLAKE_SYMBOL)
                lcd.print("*");
            else if (grid[col][row] == PLAYER_SYMBOL)
                lcd.write(byte(0));
        }
}

void SnowingGame::GenerateObstacle(void)
{
    for (int col = 0; col < cols; col++)
        if (grid[col][0] == 0x01 || grid[col][1] == 0x01)
            return;
    grid[random(0, cols)][0] = SNOWFLAKE_SYMBOL;
}

void SnowingGame::MoveObstacles(void)
{
    for (int row = rows - 1; row >= 0; row--)
        for (int col = 0; col < cols; col++)
        {
            if (grid[col][row] != SNOWFLAKE_SYMBOL)
                continue;

            if (row == rows - 1)
            {
                grid[col][row] = 0x00;
            }
            else
            {
                grid[col][row] = 0x00;
                grid[col][row + 1] = SNOWFLAKE_SYMBOL;
            }
        }
}

void SnowingGame::MovePlayer(void)
{
    for (int col = 0; col < cols; col++)
        grid[col][rows - 1] = 0x00;

    if (digitalRead(button) == LOW)
        playerColumn = (playerColumn == 0) ? 1 : 0;

    grid[playerColumn][rows - 1] = PLAYER_SYMBOL;
}

void SnowingGame::CheckCollision(void)
{
    if (grid[playerColumn][rows - 1] == SNOWFLAKE_SYMBOL)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Game Over!");
        while (true)
            ;
    }
}

SnowingGame::SnowingGame(int LCD_COLS, int LCD_ROWS, int BUTTON)
    : cols(LCD_ROWS), rows(LCD_COLS), button(BUTTON), lcd(0x27, LCD_COLS, LCD_ROWS)
{
    grid = new byte *[cols];
    for (int i = 0; i < cols; ++i)
        grid[i] = new byte[rows]();
    
    for (int i = 0; i < 8; i++)
        fullChar[i] = B11111;
    
    pinMode(button, INPUT_PULLUP);
}

SnowingGame::~SnowingGame()
{
    for (int i = 0; i < cols; ++i)
        delete[] grid[i];

    delete[] grid;
}

void SnowingGame::Init(void)
{
    lcd.init();
    lcd.backlight();
    lcd.createChar(0, fullChar);
    Serial.begin(9600);
}

void SnowingGame::Tick(void)
{
    MovePlayer();
    MoveObstacles();
    if (random(0, 2))
        GenerateObstacle();
    CheckCollision();
    DrawGrid();
}