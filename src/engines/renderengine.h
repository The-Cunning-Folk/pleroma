#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include<engine.h>
#include<spriterenderer.h>
#include<tilemap.h>

namespace BQ{

class RenderEngine : public Engine
{
public:
    RenderEngine();

    void drawTileMap(TileMap &);
    void setVisibleRegion(const sf::FloatRect &);

    std::map<std::string,SpriteSheet> spriteSheets;

    void wake();

    void start();
    void run();
    void finish();
    void drawDebug();

    sf::FloatRect visibleRegion;
};

}
#endif // RENDERENGINE_H
