#include <raylib.h>

int screenWidth = 800;
int screenHeight = 400;

int main()
{
    InitWindow(screenWidth, screenHeight, "Arkanoid");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawLine(350, 390, 450, 390, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}