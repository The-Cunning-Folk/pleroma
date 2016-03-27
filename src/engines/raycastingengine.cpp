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
    return r;
}

SimpleRay &RaycastingEngine::createOwnedRay(sf::Vector2f v1, sf::Vector2f v2, GameObject & owner)
{
    SimpleRay & r = createBasicRay(v1,v2);
    r.originator = owner.name;
    return r;
}

SimpleRay &RaycastingEngine::createOwnedRay(GameObject & owner, sf::Vector2f relativePosition)
{
    sf::Vector2f start = owner.loadTransform().position;
    sf::Vector2f end = start + relativePosition;
    return createOwnedRay(start,end,owner);
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

    //resolve rays
    for(int n=0; n<simpleRays.size(); n++)
    {
        SimpleRay & r = simpleRays[n];
        std::vector<sf::Vector2i> gridPositions = grid->bresenhamLine(r.startPosition,r.endPosition);
        for(int i=0; i<gridPositions.size(); i++)
        {
            if(!grid->isActiveGlobal(gridPositions[i])) {continue;}
            GridSquare & g = grid->getActiveGridSquareFromGlobalCoords(gridPositions[i]);
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
                            r.objectsInContact.push_back(c.getParent());
                            r.collidablesInContact.push_back(c.index);
                            r.endPosition = l.intersectionPoint;
                            gridPositions.erase(gridPositions.begin()+i,gridPositions.end());
                            continue;
                        }
                    }
                }
            }
        }

        for(int i=0; i<r.objectsInContact.size(); i++)
        {
            if(r.objectsInContact[i] == r.target)
            {
                //trigger behaviours here!

            }
            else
            {
                //secondary behaviours here1
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

