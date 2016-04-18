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

    float depth;

    sf::Vector2f offset;
    std::string texture;

    int getTransform() const;
    void setTransform(int value);

    bool operator < (const SpriteRenderer& str) const
    {
        return (depth < str.depth);
    }
};

}
#endif // SPRITERENDERER_H
