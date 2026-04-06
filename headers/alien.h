#pragma once
#include "raylib.h"

class Alien
{
    public:
    Alien(int type, Vector2 position);
    static Texture2D alienImages[3];
    static void unloadImages();
    int type;
    Vector2 position;
    void update(int direction);
    void draw();
    int getType();
};