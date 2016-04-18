#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SFML/Graphics.hpp>

class SpriteSheet
{
public:
    SpriteSheet();
    SpriteSheet(std::string, int, int, int, int);

    int xSplit; //size of the individual sprites in x
    int ySplit; //size of the individual sprites in in y

    int xSize;
    int ySize;

    sf::IntRect getSprite(int);
    sf::IntRect getSprite(int,int);

    std::string texture;

};

#endif // SPRITESHEET_H
