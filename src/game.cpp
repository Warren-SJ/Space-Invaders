#include "game.h"
Game::Game()
{
    initGame();
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
    if (!run)
    {
        return;
    }
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
    if (!run)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            reset();
            initGame();
        }
        return;
    }

    spaceship.update();
    moveAliens();
    alienShoot();
    for (auto& laser : alienLasers)
    {
        laser.update();
    }
    deleteLaser();
    mysteryShip.update();

    double currentTime = GetTime();
    if (!mysteryShip.alive && currentTime >= nextMysterySpawnTime)
    {
        mysteryShip.spawn();
        nextMysterySpawnTime = currentTime + mysteryShipSpawnInterval;
    }

    checkForCollisions();
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
        obstacles.emplace_back(Obstacle{Vector2{offsetX, float(GetScreenHeight()) - 200}});
    }
    return obstacles;
}

void Game::initGame()
{
    obstacles = createObstacles();
    aliens = createAliens();
    alienDirection = 1;
    mysteryShip.spawn();
    timeSinceLastAlienShot = 0.0f;
    nextMysterySpawnTime = GetTime() + mysteryShipSpawnInterval;
    lives = 3;
    score = 0;
    highScore = loadHighScore();
    run = true;
}

void Game::reset()
{
    spaceship.reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
}

void Game::moveAliens()
{
    for (auto& alien: aliens)
    {
        if (alien.position.x <= 25 || alien.position.x + alien.alienImages[alien.type - 1].width + 25 >= GetScreenWidth())
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
    for (auto it = alienLasers.begin(); it != alienLasers.end(); )
    {
        if (it->isActive() == false)
        {
            it = alienLasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Game::checkForCollisions()
{
    // spaceship lasers
    auto& lasers = spaceship.getLasers();
    for (auto it = lasers.begin(); it != lasers.end(); )
    {
        bool hit = false;

        for (auto alienIt = aliens.begin(); alienIt != aliens.end(); )
        {
            if (CheckCollisionRecs(it->getRect(), alienIt->getRect()))
            {
                score += alienIt->getType() * 100;
                alienIt = aliens.erase(alienIt);
                hit = true;
                break;
            }
            else
            {
                ++alienIt;
            }
        }

        if (!hit)
        {
            for (auto& obstacle : obstacles)
            {
                for (auto blockIt = obstacle.blocks.begin(); blockIt != obstacle.blocks.end(); )
                {
                    if (CheckCollisionRecs(it->getRect(), blockIt->getRect()))
                    {
                        blockIt = obstacle.blocks.erase(blockIt);
                        hit = true;
                        break;
                    }
                    else
                    {
                        ++blockIt;
                    }
                }

                if (hit)
                {
                    break;
                }
            }
        }

        if (!hit)
        {
            if (CheckCollisionRecs(it->getRect(), mysteryShip.getRect()))
            {
                score += 500;
                mysteryShip.alive = false;
                hit = true;
            }
        }

        if (hit)
        {
            it = lasers.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // alien lasers
    auto& alienlasers = alienLasers;
    for (auto it = alienlasers.begin(); it != alienlasers.end(); )
    {
        bool hit = false;

        if (CheckCollisionRecs(it->getRect(), spaceship.getRect()))
        {
            hit = true;
            lives--;
            if (lives <= 0)
            {
                gameOver();
            }
        }

        if (!hit)
        {
            for (auto& obstacle : obstacles)
            {
                for (auto blockIt = obstacle.blocks.begin(); blockIt != obstacle.blocks.end(); )
                {
                    if (CheckCollisionRecs(it->getRect(), blockIt->getRect()))
                    {
                        blockIt = obstacle.blocks.erase(blockIt);
                        hit = true;
                        break;
                    }
                    else
                    {
                        ++blockIt;
                    }
                }

                if (hit)
                {
                    break;
                }
            }
        }
        if (hit)
        {
            it = alienLasers.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // alien and obstacles
    for (auto& alien: aliens)
    {
        for (auto& obstacle: obstacles)
        {
            for (auto blockIt  = obstacle.blocks.begin(); blockIt != obstacle.blocks.end(); )
            {
                if (CheckCollisionRecs(alien.getRect(), blockIt->getRect()))
                {
                    blockIt = obstacle.blocks.erase(blockIt);
                }
                else
                {
                    ++blockIt;
                }
            }
        }
        if (CheckCollisionRecs(alien.getRect(), spaceship.getRect()))
        {
            gameOver();
        }
    }
}

void Game::gameOver()
{
    run = false;
    if (score > highScore)
    {
        saveHighScore();
    }
}

void Game::saveHighScore()
{
    std::ofstream file("highscore.txt");
    if (file.is_open())
    {
        file << score;
        file.close();
    }
    else
    {
        return;
    }
}

int Game::loadHighScore()
{
    int loadedHighScore = 0;
    std::ifstream file("highscore.txt");
    if (file.is_open())
    {
        file >> loadedHighScore;
        file.close();
        return loadedHighScore;
    }
    return 0;
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
    }
}
