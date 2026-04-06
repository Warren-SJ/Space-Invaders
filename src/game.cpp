#include "game.h"

Game::Game()
{
    obstacles = createObstacles();
}

Game::~Game()
{
}

void Game::draw()
{
	spaceship.draw();
    for (Obstacle& obstacle : obstacles)
    {
        obstacle.draw();
    }
}

void Game::handleInput()
{
    if (IsKeyDown(KEY_LEFT))
    {
        spaceship.moveLeft();
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        spaceship.moveRight();
    }
    if (IsKeyPressed(KEY_SPACE))
    {
        spaceship.fire();
    }
}

void Game::update()
{
    spaceship.update();
}

std::vector<Obstacle> Game::createObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;
    for (int i = 0; i < 4; i++)
    {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.emplace_back(Obstacle{Vector2{offsetX, float(GetScreenHeight()) - 100}});
    }
    return obstacles;
}
