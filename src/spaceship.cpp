#include "spaceship.h"
#include "raylib.h"

Spaceship::Spaceship()
{
	spaceshipTexture = LoadTexture("assets/spaceship.png");
	position = { float(GetScreenWidth() - spaceshipTexture.width)/2 , float(GetScreenHeight() - spaceshipTexture.height - 100) };
}

Spaceship::~Spaceship()
{
	UnloadTexture(spaceshipTexture);
}

Vector2 Spaceship::GetPosition()
{
    return position;
}

void Spaceship::draw()
{
	DrawTexture(spaceshipTexture, position.x, position.y, WHITE);
}

void Spaceship::moveLeft()
{
	position.x -= 5;
	if (position.x < 25)
	{
		position.x = 25;
	}
}

void Spaceship::moveRight()
{
	position.x += 5;
	if (position.x > GetScreenWidth() - spaceshipTexture.width - 25)
	{
		position.x = GetScreenWidth() - spaceshipTexture.width - 25;
	}
}

void Spaceship::fire()
{
	lasers.emplace_back(Laser({position.x + spaceshipTexture.width/2, position.y - 20}, -5));
}

void Spaceship::update()
{
	for (auto laser = lasers.begin(); laser != lasers.end(); )
	{
		laser->update();
		if (!laser->isActive())
		{
			laser = lasers.erase(laser);
		}
		else
		{
			++laser;
		}
	}
}

Rectangle Spaceship::getRect()
{
    return {position.x, position.y, float(spaceshipTexture.width), float(spaceshipTexture.height)};
}

void Spaceship::reset()
{
    position = { float(GetScreenWidth() - spaceshipTexture.width)/2, float(GetScreenHeight() - spaceshipTexture.height - 100) };
    lasers.clear();
}

std::vector<Laser>& Spaceship::getLasers()
{
    return lasers;
}
