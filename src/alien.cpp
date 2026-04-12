#include "alien.h"
#include <string>

Texture2D Alien::alienImages[3] = {};

Alien::Alien(int type, Vector2 position): type(type), position(position)
{
    if (alienImages[type - 1].id == 0)
    {
        std::string path = "assets/alien_" + std::to_string(type) + ".png";
        alienImages[type - 1] = LoadTexture(path.c_str());
    }
}

void Alien::update(int direction)
{
    position.x += direction;
}

void Alien::draw()
{
    DrawTexture(alienImages[type - 1], position.x, position.y, WHITE);
}

int Alien::getType()
{
    return type;
}

Rectangle Alien::getRect()
{
    return {position.x, position.y, float(alienImages[type - 1].width), float(alienImages[type - 1].height)};
}

void Alien::unloadImages()
{
    for (int i = 0; i < 3; i++)
    {
        if (alienImages[i].id != 0)
        {
            UnloadTexture(alienImages[i]);
            alienImages[i] = {};
        }
    }
}