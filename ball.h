#pragma once
#include "raylib.h"

class ball
{
private:
public:
    float x, y;
    float r;
    float speedX, speedY;
    ball()
    {
        resetBall();
    };

    void resetBall()
    {
        x = 400.0f;
        y = 200.0f;
        r = 5.0f;
        speedX = 200.0f;
        speedY = 200.0f;
    }
};