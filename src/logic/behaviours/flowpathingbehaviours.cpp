#include "flowpathingbehaviours.h"

#include <gameobject.h>
#include<componentloader.h>
#include<gameobjectloader.h>


using namespace BQ;

FlowPathingBehaviours::FlowPathingBehaviours()
{
    pathSpeed=50;
}


void FlowPathingBehaviours::collisionWith(BQ::GameObject & o, std::string ca, std::string cb)
{

}

void FlowPathingBehaviours::resolveEvents()
{

}

void FlowPathingBehaviours::update()
{
    int transform =  gameObjectLoader->loadGameObject(parent).transform;
    Transform & t = componentLoader->getTransform( gameObjectLoader->loadGameObject(parent).transform);
    sf::Vector2i gPos = grid->getGridPosition(t.position);

    GridSquare & g = grid->getActiveGridSquareFromGlobalCoords(gPos);

    t.move(delta*pathSpeed*maths->unit(g.pathVector));
}
