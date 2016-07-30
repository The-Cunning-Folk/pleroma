#ifndef SPRITERENDERERPATTERN_H
#define SPRITERENDERERPATTERN_H

#include <factorypattern.h>

namespace BQ
{

class SpriteRendererPattern : public FactoryPattern
{
public:
    SpriteRendererPattern();

    std::string clip;
    std::string sheet;
    sf::Vector2f offset;
    float depthOffset;
    bool paused;
    float spf;

};

}
#endif // SPRITERENDERERPATTERN_H
