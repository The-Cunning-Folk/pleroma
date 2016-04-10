#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include<engine.h>
#include<spriterenderer.h>

namespace BQ{

class RenderEngine : public Engine
{
public:
    RenderEngine();

    std::vector<SpriteRenderer> sprites;

    SpriteRenderer& addSpriteRenderer();
    SpriteRenderer& getSpriteRenderer(int);

    void start();
    void run();
    void finish();
    void drawDebug();

    std::vector<SpriteRenderer> getSprites() const;
    void setSprites(const std::vector<SpriteRenderer> &value);
};

}
#endif // RENDERENGINE_H
