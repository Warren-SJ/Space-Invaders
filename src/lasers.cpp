#include "lasers.h"

Laser::Laser(Vector2 position, int speed) : position(position), speed(speed)
{
}

Laser::~Laser()
{

}

void Laser::update()
{
    position.y += speed;
    draw();
}

void Laser::draw()
{
    DrawRectangle(position.x, position.y, 4, 15, {243, 216, 16, 255});
}

bool Laser::isActive()
{
    if (position.y < 0 || position.y > GetScreenHeight())
    {
        return false;
    } 
    return true;
}
