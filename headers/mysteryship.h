#pragma once
#include "raylib.h"

class MysteryShip
{
    public:
        MysteryShip();
        ~MysteryShip();
        void update();
        void draw();
        void spawn();
    private:
        Vector2 position;
        Texture2D texture;
        int speed;
        bool alive;
}; 