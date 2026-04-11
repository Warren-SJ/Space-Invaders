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
    position.y = 35;
    int side = GetRandomValue(0, 1);
    position.x = side * (GetScreenWidth() - texture.width) + (side - 1) * -texture.width;
    speed = side == 0 ? 3 : -3;
    alive = true;
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
