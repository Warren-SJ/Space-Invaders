#pragma once
#include "raylib.h"
#include "spaceship.h"
#include "obstacle.h"

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
    std::vector<Obstacle> obstacles;
    std::vector<Obstacle> createObstacles();
};