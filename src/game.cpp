#include "game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::draw()
{
	spaceship.draw();
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
