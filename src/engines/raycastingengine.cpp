#include "raycastingengine.h"

#include<game.h>

using namespace BQ;

RaycastingEngine::RaycastingEngine()
{

}

SimpleRay &RaycastingEngine::createBasicRay(sf::Vector2f v1, sf::Vector2f v2)
{
    simpleRays.resize(simpleRays.size()+1);
    SimpleRay & r = simpleRays.back();
    r.startPosition = v1;
    r.targetPosition = v2;
    r.endPosition = v2;
    std::vector<sf::Vector2i> gridSquares = grid->bresenhamLine(v1,v2);
    r.gridPositions = gridSquares;
    return r;
}

SimpleRay &RaycastingEngine::createOwnedRay(sf::Vector2f v1, sf::Vector2f v2, GameObject & owner)
{
    SimpleRay & r = createBasicRay(v1,v2);
    r.originator = owner.name;
    return r;
}

SimpleRay &RaycastingEngine::createTargettedRay(GameObject & owner, GameObject & target)
{
    SimpleRay & r = createOwnedRay(owner.loadTransform().position,target.loadTransform().position,owner);
    r.target = target.name;
    return r;
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

    for(int n=0; n<simpleRays.size(); n++)
    {
        SimpleRay & r = simpleRays[n];
        for(int i=0; i<r.gridPositions.size(); i++)
        {
            if(!grid->isActiveGlobal(r.gridPositions[i])) {continue;}
            GridSquare & g = grid->getActiveGridSquareFromGlobalCoords(r.gridPositions[i]);
            g.debugColor = sf::Color::Yellow;
            if(g.collidablesInContact.size() > 0)
            {
                //find entry point at edge of this
                for(int j=0; j<g.collidablesInContact.size(); j++)
                {
                    Collidable & c = componentLoader->getCollidable(g.collidablesInContact[j]);
                    if(c.getParent() != r.originator)
                    {
                        LineIntersection l = maths->findIntersection(r.startPosition,r.endPosition,c.polygon);
                        if(l.intersects)
                        {
                            r.endPosition = l.intersectionPoint;
                            continue;
                        }
                    }
                }
            }
        }
    }
}

void RaycastingEngine::finish()
{
    
}

void RaycastingEngine::drawDebug()
{
    sf::VertexArray drawRays(sf::Lines,2*simpleRays.size());

    for(int i=0; i<simpleRays.size(); i++)
    {
        SimpleRay & r = simpleRays[i];
        drawRays[2*i].position=r.startPosition;
        drawRays[2*i+1].position=r.endPosition;
    }

    gameWindow->draw(drawRays);
}

