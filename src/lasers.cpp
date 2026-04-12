#include "lasers.h"

Laser::Laser(Vector2 position, int speed) : position(position), speed(speed)
{
}

Laser::~Laser()
{
}

void Laser::update()
{
    if (isActive())
    {
        position.y += speed;
        draw();
    }
}

void Laser::draw()
{
    DrawRectangle(position.x, position.y, 4, 15, {243, 216, 16, 255});
}

bool Laser::isActive()
{
    if (position.y < 25 || position.y >= 715)
    {
        return false;
    } 
    return true;
}

Vector2 Laser::getPosition()
{
    return position;
}

Rectangle Laser::getRect()
{
    return {position.x, position.y, 4, 15};
}
