#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SFML/Graphics.hpp>
#include <sprite.h>

namespace BQ{
class SpriteSheet
{
public:
    SpriteSheet();

    std::string texture;
    std::map<std::string,Sprite> sprites;
    std::map<int,std::string> spriteFrameMap;

    void addSprite(std::string,Sprite);

    Sprite & getSprite(std::string);
    Sprite & getSprite(int);

};
}

#endif // SPRITESHEET_H
