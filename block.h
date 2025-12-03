#pragma once
#include <raylib.h>

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