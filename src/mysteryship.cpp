#include "mysteryship.h"

MysteryShip::MysteryShip()
{
    texture = LoadTexture("Graphics/mystery.png");
    alive = false;
}

MysteryShip::~MysteryShip()
{
    UnloadTexture(texture);
}

void MysteryShip::spawn()
{
    position.y = GetRandomValue(20, 60);
    int side = GetRandomValue(0, 1);
    if (side == 0)
    {
        position.x = -texture.width;
        speed = 3;
    }
    else
    {
        position.x = GetScreenWidth();
        speed = -3;
    }
    alive = true;
}

Rectangle MysteryShip::getRect()
{
    if (alive)
    {
        return {position.x, position.y, float(texture.width), float(texture.height)};
    }
    return {0, 0, 0, 0};
}

void MysteryShip::update()
{
    if (alive)
    {
        position.x += speed;
        if (position.x < -texture.width || position.x > GetScreenWidth())
            alive = false;
    }
}

void MysteryShip::draw()
{
    if (alive)
        DrawTexture(texture, position.x, position.y, WHITE);
}
