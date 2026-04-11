#pragma once
#include <raylib.h>
#include "lasers.h"
#include <vector>

class Spaceship
{
public:
	Spaceship();
	~Spaceship();
	Vector2 GetPosition();
	void draw();
	void moveLeft();
	void moveRight();
	void fire();
    void update();
	Rectangle getRect();
	std::vector<Laser>& getLasers();

private:
    Texture2D spaceshipTexture;
	Vector2 position;
	std::vector<Laser> lasers;
};