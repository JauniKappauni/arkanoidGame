#include <raylib.h>
#include <string>
using namespace std;
#define ROWS_OF_BLOCKS 5
#define COLUMNS_OF_BLOCKS 14

int screenWidth = 800;
int screenHeight = 400;

float posX = 350.0f;

float speed = 500.0f;

float ballX = 400.0f;
float ballY = 200.0f;
float ballR = 5.0f;
float ballSpeedX = 300.0f;
float ballSpeedY = 300.0f;

float blockWidth = 50.0f;
float blockHeight = 25.0f;
float blockSpace = 5.0f;

int score = 0;
int lives = 3;
bool isGameStarted = false;

class block
{
private:
    Vector2 pos;
    bool active;

public:
    block(Vector2 x, bool active);
    ~block();
    bool isActive()
    {
        return active;
    }
    void deactive()
    {
        active = false;
    }
    Vector2 getPos()
    {
        return pos;
    }
};

block::block(Vector2 x, bool y)
{
    pos = x;
    active = y;
}

block::~block()
{
}

block *blocks[ROWS_OF_BLOCKS][COLUMNS_OF_BLOCKS];

int main()
{
    InitWindow(screenWidth, screenHeight, "Arkanoid");
    for (int i = 0; i < ROWS_OF_BLOCKS; i++)
    {
        for (int j = 0; j < COLUMNS_OF_BLOCKS; j++)
        {
            float x = blockSpace + j * (blockWidth + blockSpace);
            float y = blockSpace + i * (blockHeight + blockSpace);
            blocks[i][j] = new block({x, y}, true);
        }
    }
    while (!WindowShouldClose())
    {
        if (!isGameStarted)
        {
            Vector2 mouse = GetMousePosition();
            Rectangle btn = {300, 100, 200, 100};
            Rectangle btn2 = {300, 250, 200, 100};
            BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangleRec(btn, GRAY);
            DrawRectangleRec(btn2, GRAY);
            DrawText("Start", 370, 150, 20, WHITE);
            DrawText("Quit", 370, 300, 20, WHITE);
            EndDrawing();
            if (CheckCollisionPointRec(mouse, btn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                isGameStarted = true;
            }
            if (CheckCollisionPointRec(mouse, btn2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                CloseWindow();
            }
            continue;
        }
        if (lives != 0)
        {
            float dt = GetFrameTime();
            BeginDrawing();
            ClearBackground(BLACK);

            DrawLine(posX, 390, posX + 100, 390, WHITE);
            if (IsKeyDown(KEY_A) && posX > 0)
            {
                posX -= speed * dt;
            }
            if (IsKeyDown(KEY_D) && posX < screenWidth - 100)
            {
                posX += speed * dt;
            }
            DrawCircle(ballX, ballY, ballR, WHITE);
            ballX += ballSpeedX * dt;
            ballY += ballSpeedY * dt;
            if (ballY < 0)
            {
                ballSpeedY *= -1;
            }
            if (ballY >= 390 && ballX >= posX && ballX <= posX + 100)
            {
                ballSpeedY *= -1;
            }
            if (ballX > screenWidth)
            {
                ballSpeedX *= -1;
            }
            if (ballX < 0)
            {
                ballSpeedX *= -1;
            }
            if (ballY > screenHeight)
            {
                lives--;
                ballY = 200.0f;
            }
            for (int i = 0; i < ROWS_OF_BLOCKS; i++)
            {
                for (int j = 0; j < COLUMNS_OF_BLOCKS; j++)
                {
                    block *b = blocks[i][j];
                    if (!b->isActive())
                        continue;

                    Vector2 pos = b->getPos();

                    DrawRectangle(pos.x, pos.y, blockWidth, blockHeight, WHITE);
                    if (ballX >= pos.x && ballX <= pos.x + blockWidth && ballY > pos.y && ballY < pos.y + blockHeight)
                    {
                        b->deactive();
                        ballSpeedY *= -1;
                        score++;
                        ballSpeedY = ballSpeedY ? ballSpeedY + score : ballSpeedY - score;
                    }
                }
            }
            string scoreStr = to_string(score);
            DrawText(scoreStr.data(), 10, 10, 25, RED);
            string livesStr = to_string(lives);
            DrawText(livesStr.data(), 10, 375, 25, WHITE);
            EndDrawing();
        }
        else
        {
            isGameStarted = false;
            score = 0;
            lives = 3;
            ballX = 400.0f;
            ballY = 200.0f;
            ballSpeedX = 300.0f;
            ballSpeedY = 300.0f;
            posX = 350.0f;
            for (int i = 0; i < ROWS_OF_BLOCKS; i++)
            {
                for (int j = 0; j < COLUMNS_OF_BLOCKS; j++)
                {
                    float x = blockSpace + j * (blockWidth + blockSpace);
                    float y = blockSpace + i * (blockHeight + blockSpace);
                    blocks[i][j] = new block({x, y}, true);
                }
            }
            Vector2 mouse = GetMousePosition();
            Rectangle btn = {300, 100, 200, 100};
            Rectangle btn2 = {300, 250, 200, 100};
            BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangleRec(btn, GRAY);
            DrawRectangleRec(btn2, GRAY);
            DrawText("Start", 370, 150, 20, WHITE);
            DrawText("Quit", 370, 300, 20, WHITE);
            EndDrawing();
            if (CheckCollisionPointRec(mouse, btn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                isGameStarted = true;
            }
            if (CheckCollisionPointRec(mouse, btn2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                CloseWindow();
            }
            continue;
        }
    }
    CloseWindow();
    return 0;
}
