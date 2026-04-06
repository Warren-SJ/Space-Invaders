#include "game.h"

Game::Game()
{
    obstacles = createObstacles();
    aliens = createAliens();
    alienDirection = 1;
}

Game::~Game()
{
    Alien::unloadImages();
}

void Game::draw()
{
	spaceship.draw();
    for (Obstacle& obstacle : obstacles)
    {
        obstacle.draw();
    }
    for (Alien& alien : aliens)
    {
        alien.draw();
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
    moveAliens();
}

std::vector<Alien> Game::createAliens()
{
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 11; col++)
        {
            int type = row / 2 + 1;
            aliens.emplace_back(Alien{type, Vector2{float(75 + col * 55), float(110 + row * 55)}});
        }
    }
    return aliens;
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

void Game::moveAliens()
{
    for (auto& alien: aliens)
    {
        if (alien.position.x <= 0 || alien.position.x + alien.alienImages[alien.type - 1].width >= GetScreenWidth())
        {
            alienDirection *= -1;
            break;
        }
    }
    for (Alien& alien : aliens)
    {
        alien.update(alienDirection);
    }
}
