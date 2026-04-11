#pragma once
#include <vector>
#include "raylib.h"
#include "spaceship.h"
#include "obstacle.h"
#include "alien.h"
#include "mysteryship.h"

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
    MysteryShip mysteryShip;
    std::vector<Laser> alienLasers;
    std::vector<Alien> createAliens();
    std::vector<Obstacle> createObstacles();
    void moveAliens();
    void moveDownAliens(int distance);
    void alienShoot();
    void deleteLaser();
    constexpr static float alienLaserShootInterval = 0.35f;
    constexpr static float mysteryShipSpawnInterval = 30.0f;
    float timeSinceLastAlienShot;
    double nextMysterySpawnTime;
    void checkForCollisions();
};
