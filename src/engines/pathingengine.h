#ifndef PATHINGENGINE_H
#define PATHINGENGINE_H

#include <engine.h>

namespace BQ{

class PathingEngine : public Engine
{
public:
    PathingEngine();

    void doWaveFront(sf::Vector2i);

    void run();
    void drawDebug();
};

}

#endif // PATHINGENGINE_H
