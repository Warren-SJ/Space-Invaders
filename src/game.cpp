#include "game.h"

Game::Game()
{
    obstacles = createObstacles();
    aliens = createAliens();
    alienDirection = 1;
    mysteryShip.spawn();
    timeSinceLastAlienShot = 0.0f;
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
    mysteryShip.draw();
    for (Laser& laser : alienLasers)
    {
        laser.draw();
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
    alienShoot();
    for (auto& laser : alienLasers)
    {
        laser.update();
    }
    mysteryShip.update();
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
            moveDownAliens(4);
            break;
        }
    }
    for (Alien& alien : aliens)
    {
        alien.update(alienDirection);
    }
}

void Game::moveDownAliens(int distance)
{
    for (Alien& alien: aliens)
    {
        alien.position.y += distance;
    }
}

void Game::deleteLaser()
{
    for(auto it = alienLasers.begin(); it != alienLasers.end(); )
    {
        if(it->getPosition().y < 0 || it->getPosition().y > GetScreenHeight())
        {
            it = alienLasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Game::alienShoot()
{
    double currentTime = GetTime();
    if (currentTime - timeSinceLastAlienShot >= alienLaserShootInterval && !aliens.empty())
    {
    int randomIndex = GetRandomValue(0, aliens.size() - 1);
    Alien& shooter = aliens[randomIndex];
    alienLasers.emplace_back(Laser(Vector2
        (float(shooter.position.x + shooter.alienImages[shooter.type - 1].width / 2), float(shooter.position.y + shooter.alienImages[shooter.type - 1].height)),
         6));
    timeSinceLastAlienShot = currentTime;
    deleteLaser();
    }
}
