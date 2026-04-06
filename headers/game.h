#pragma once
#include "raylib.h"
#include "spaceship.h"
#include "obstacle.h"
#include "alien.h"

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
    std::vector<Alien> aliens;
    int alienDirection;
    std::vector<Alien> createAliens();
    std::vector<Obstacle> createObstacles();
    void moveAliens();
};