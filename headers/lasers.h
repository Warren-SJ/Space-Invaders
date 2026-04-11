#pragma once
#include "raylib.h"

class Laser
{
    public:
        Laser(Vector2 position, int speed);
        ~Laser();
        void update();
        void draw();
        bool isActive();
        Vector2 getPosition();
    private:
        Vector2 position;
        int speed;
};
