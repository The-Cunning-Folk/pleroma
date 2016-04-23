#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <component.h>
#include <spritesheet.h>

namespace BQ{

class SpriteRenderer : public Component
{
public:
    SpriteRenderer();

    int transform;

    bool centreOrigin;

    float depth;

    sf::Vector2f offset; //where the sprite sits compared to the transform position
    float depthOffset; //a correction for the draw order sorting

    std::string texture;
    sf::IntRect textureRect;

    int getTransform() const;
    void setTransform(int value);

    bool operator < (const SpriteRenderer& str) const
    {
        return (depth < str.depth);
    }
};

}
#endif // SPRITERENDERER_H
