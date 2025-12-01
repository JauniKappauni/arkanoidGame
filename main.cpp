#include <raylib.h>

int screenWidth = 800;
int screenHeight = 400;

float posX = 350.0f;

float speed = 500.0f;

float ballX = 400.0f;
float ballY = 200.0f;
float ballR = 5.0f;
float ballSpeedX = 300.0f;
float ballSpeedY = 300.0f;

int main()
{
    InitWindow(screenWidth, screenHeight, "Arkanoid");
    while (!WindowShouldClose())
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
        EndDrawing();
    }
    CloseWindow();
    return 0;
}