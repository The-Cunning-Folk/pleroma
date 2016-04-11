#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <component.h>

namespace BQ{

class SpriteRenderer : public Component
{
public:
    SpriteRenderer();

    int transform;

    bool centreOrigin;

    sf::Vector2f offset;
    std::string texture;

    int getTransform() const;
    void setTransform(int value);
};

}
#endif // SPRITERENDERER_H
