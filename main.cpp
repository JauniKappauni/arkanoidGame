#include <raylib.h>

int screenWidth = 800;
int screenHeight = 400;

float posX = 350.0f;

float speed = 100.0f;

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
        EndDrawing();
    }
    CloseWindow();
    return 0;
}