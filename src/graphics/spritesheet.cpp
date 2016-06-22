#include "spritesheet.h"

using namespace BQ;

SpriteSheet::SpriteSheet()
{
    texture = "";
}

void SpriteSheet::addSprite(std::string name, std::vector<sf::IntRect> frames)
{
    spriteFrames[name] = frames;
    spriteFrameMap[spriteFrameMap.size()] = name;
}

std::vector<sf::IntRect> &SpriteSheet::getSprite(std::string sprite)
{
    if(spriteFrames.find(sprite) != spriteFrames.end())
    {
        return spriteFrames[sprite];
    }
    else
    {
        return spriteFrames.begin()->second;
    }
}

std::vector<sf::IntRect> &SpriteSheet::getSprite(int index)
{
    return getSprite(spriteFrameMap[index]);
}
