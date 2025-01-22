#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class SnowingGame
{
private:
    byte** grid;
    int cols;
    int rows;
    int button;
    int playerColumn = 0;
    byte fullChar[8];
    byte playerCol = 0x00;
    LiquidCrystal_I2C lcd;
    void ClearGrid(void);
    void DrawGrid(void);
    void GenerateObstacle(void);
    void MoveObstacles(void);
    void MovePlayer(void);
    void CheckCollision(void);
public:
    SnowingGame(int LCD_COLS, int LCD_ROWS, int BUTTON);
    ~SnowingGame();
    void Init(void);
    void Tick(void);
};