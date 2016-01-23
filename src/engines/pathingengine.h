#ifndef PATHINGENGINE_H
#define PATHINGENGINE_H

#include <engine.h>

namespace BQ{

class PathingEngine : public Engine
{
public:
    PathingEngine();

    void doWaveFront(GridSquare &);
    void doWaveFrontLayer(int,std::vector<sf::Vector2i>);

    std::vector<sf::Vector2f> goals;

    void addGoal(sf::Vector2f);

    void run();
    void drawDebug();
};

}

#endif // PATHINGENGINE_H
