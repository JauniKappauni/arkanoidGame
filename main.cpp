#include <raylib.h>
#define ROWS_OF_BLOCKS 5
#define COLUMNS_OF_BLOCKS 3

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
                }
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
