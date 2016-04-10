#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <component.h>

namespace BQ{

class SpriteRenderer : public Component
{
public:
    SpriteRenderer();

    std::string texture;

};

}
#endif // SPRITERENDERER_H
