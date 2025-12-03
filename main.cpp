#include <raylib.h>
#include <string>
#include "block.h"
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
float ballSpeedX = 200.0f;
float ballSpeedY = 200.0f;

float blockWidth = 50.0f;
float blockHeight = 25.0f;
float blockSpace = 5.0f;

int score = 0;
int lives = 3;
bool isGameStarted = false;
bool startLoop = false;

float timerStart = 0.0f;
int countdown = 3;
bool countdownActive = false;
bool pauseMenuActive = false;



block::block(Vector2 x, bool y)
{
    pos = x;
    active = y;
}

block::~block()
{
}

block *blocks[ROWS_OF_BLOCKS][COLUMNS_OF_BLOCKS];
int quantity = ROWS_OF_BLOCKS * COLUMNS_OF_BLOCKS;

int main()
{
    InitWindow(screenWidth, screenHeight, "Arkanoid");
    InitAudioDevice();
    SetExitKey(KEY_NULL);
    Sound hit = LoadSound("resources/arkanoid-sfx-1.mp3");
    Sound noHit = LoadSound("resources/arkanoid-sfx-2.mp3");
    Sound gameStart = LoadSound("resources/arkanoid-sfx-9.mp3");
    Sound gameOver = LoadSound("resources/arkanoid-sfx-11.mp3");
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
        if (IsKeyPressed(KEY_P))
        {
            pauseMenuActive = !pauseMenuActive;
        }
        if (pauseMenuActive)
        {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Pause Menu", 400, 200, 50, WHITE);
            EndDrawing();
            continue;
        }
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
                PlaySound(gameStart);
            }
            if (CheckCollisionPointRec(mouse, btn2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                CloseWindow();
            }
            continue;
        }
        if (!startLoop)
        {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Press Space to start game loop", 400, 200, 20, WHITE);
            if (IsKeyPressed(KEY_SPACE))
            {
                startLoop = true;
            }
            EndDrawing();
            continue;
        }
        if (score == quantity)
        {
            if (!countdownActive)
            {
                countdownActive = true;
                timerStart = GetTime();
                countdown = 3;
            }
            float elapsed = GetTime() - timerStart;

            if (elapsed >= 1.0f)
            {
                countdown--;
                timerStart = GetTime();
            }
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("You won!", 400, 200, 20, WHITE);
            string countdownStr = to_string(countdown);
            DrawText(countdownStr.data(), 500, 200, 20, WHITE);
            EndDrawing();
            if (countdown < 0)
            {
                isGameStarted = false;
                startLoop = false;
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
                PlaySound(noHit);
            }
            if (ballY >= 390 && ballX >= posX && ballX <= posX + 100)
            {
                ballSpeedY *= -1;
            }
            if (ballX > screenWidth)
            {
                ballSpeedX *= -1;
                PlaySound(noHit);
            }
            if (ballX < 0)
            {
                ballSpeedX *= -1;
                PlaySound(noHit);
            }
            if (ballY > screenHeight)
            {
                lives--;
                ballY = 200.0f;
                PlaySound(gameOver);
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
                        PlaySound(hit);
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
            startLoop = false;
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
                PlaySound(gameStart);
            }
            if (CheckCollisionPointRec(mouse, btn2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                CloseWindow();
            }
            continue;
        }
    }
    UnloadSound(hit);
    UnloadSound(noHit);
    UnloadSound(gameStart);
    UnloadSound(gameOver);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
