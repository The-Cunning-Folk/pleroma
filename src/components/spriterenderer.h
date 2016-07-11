#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <component.h>
#include <spritesheet.h>
#include <animation.h>

namespace BQ{

class SpriteRenderer : public Component
{
public:
    SpriteRenderer();

    Animation animation;

    bool centreOrigin;

    float depth;

    sf::Vector2f offset; //where the sprite sits compared to the transform position
    float depthOffset; //a correction for the draw order sorting

    std::string texture;

    std::string spritesheet;
    std::string clip;
    int frame;

    sf::IntRect textureRect;


    void update();
    void wake();

    bool operator < (const SpriteRenderer& str) const
    {
        return (depth < str.depth);
    }
};

}
#endif // SPRITERENDERER_H
