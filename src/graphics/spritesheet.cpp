#include "spritesheet.h"

SpriteSheet::SpriteSheet()
{
    texture = "";
    xSize = 0;
    ySize = 0;
    xSplit = 0;
    ySplit = 0;
}

SpriteSheet::SpriteSheet(std::string texture, int xSize, int ySize, int xSplit, int ySplit)
{
    this->texture = texture;
    this->xSize = xSize;
    this->ySize = ySize;
    this->xSplit = xSplit;
    this->ySplit = ySplit;
}

sf::IntRect SpriteSheet::getSprite(int p)
{
    if(xSize==0||ySize==0||xSplit==0||ySplit==0)
    {
        return sf::IntRect(0,0,0,0);
    }

    int xCells = xSize/xSplit;
    int y = p/xCells;
    int x = p%xCells;

    sf::IntRect textRect;
    textRect.left = x*xSplit;
    textRect.top = y*ySplit;
    textRect.width = xSplit;
    textRect.height = ySplit;
    return textRect;
}

sf::IntRect SpriteSheet::getSprite(int x, int y)
{
    if(xSize==0||ySize==0||xSplit==0||ySplit==0)
    {
        return sf::IntRect(0,0,0,0);
    }
    sf::IntRect textRect;
    textRect.left = x*xSplit;
    textRect.top = y*ySplit;
    textRect.width = xSplit;
    textRect.height = ySplit;
    return textRect;
}

