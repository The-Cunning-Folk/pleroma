#ifndef SPRITERENDERERPATTERN_H
#define SPRITERENDERERPATTERN_H

#include <SFML/Graphics.hpp>
#include <string>

namespace BQ
{

class SpriteRendererPattern
{
public:
    SpriteRendererPattern();

    std::string clip;
    std::string sheet;
    std::string name;
    sf::Vector2f offset;
    float depthOffset;

};

}
#endif // SPRITERENDERERPATTERN_H
