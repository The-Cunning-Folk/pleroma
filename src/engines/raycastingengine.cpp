#include "raycastingengine.h"

using namespace BQ;

RaycastingEngine::RaycastingEngine()
{

}

SimpleRay &RaycastingEngine::drawRay(sf::Vector2f v1, sf::Vector2f v2)
{
    simpleRays.resize(simpleRays.size()+1);
    SimpleRay & r = simpleRays.back();
    r.startPosition = v1;
    r.targetPosition = v2;

    std::vector<sf::Vector2i> gridSquares = grid->bresenhamLine(v1,v2);

    for(int i=0; i<gridSquares.size(); i++)
    {
        GridSquare & g = grid->getActiveGridSquareFromGlobalCoords(gridSquares[i]);
        g.debugColor = sf::Color::Yellow;
    }

}

std::vector<SimpleRay> RaycastingEngine::getSimpleRays() const
{
    return simpleRays;
}

void RaycastingEngine::setSimpleRays(const std::vector<SimpleRay> &value)
{
    simpleRays = value;
}

void RaycastingEngine::start()
{
    //get rid of the rays from the last frame
    simpleRays.clear();
}

void RaycastingEngine::run()
{
    
}

void RaycastingEngine::finish()
{
    
}

void RaycastingEngine::drawDebug()
{
    
}

