#pragma once
#include "raylib.h"
#include "spaceship.h"

class Game
{
public:
    Game();
    ~Game();
    void draw();
    void handleInput();
    void update();
private:
    Spaceship spaceship;
};