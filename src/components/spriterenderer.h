#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <component.h>

namespace BQ{

class SpriteRenderer : public Component
{
public:
    SpriteRenderer();

    sf::Vector2f position;
    std::string texture;

};

}
#endif // SPRITERENDERER_H
