#include "spritesheet.h"

using namespace BQ;

SpriteSheet::SpriteSheet()
{
    texture = "error.png";
}

void SpriteSheet::addSprite(std::string name, Sprite spr)
{
    sprites[name] = spr;
    spriteFrameMap[spriteFrameMap.size()] = name;
}

Sprite &SpriteSheet::getSprite(std::string sprite)
{
    if(sprites.find(sprite) != sprites.end())
    {
        return sprites[sprite];
    }
    else
    {
        return sprites.begin()->second;
    }
}

Sprite &SpriteSheet::getSprite(int index)
{
    return getSprite(spriteFrameMap[index]);
}
