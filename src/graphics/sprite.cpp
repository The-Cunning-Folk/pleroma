#include "sprite.h"

using namespace BQ;

Sprite::Sprite()
{
    offset.x = 0;
    offset.y = 0;
}

sf::IntRect Sprite::getFrame(int index)
{
    if(index >=0 && index < frames.size())
    {
        return frames[index];
    }
    else
    {
        return sf::IntRect(0,0,0,0);
    }
}

