#include "flowpathingbehaviours.h"

#include <gameobject.h>
#include<componentloader.h>
#include<gameobjectloader.h>


using namespace BQ;

FlowPathingBehaviours::FlowPathingBehaviours()
{

}


void FlowPathingBehaviours::collisionWith(BQ::GameObject & o, std::string ca, std::string cb)
{

}

void FlowPathingBehaviours::resolveEvents()
{

}

void FlowPathingBehaviours::update()
{

    Transform & t = componentLoader->getTransform( gameObjectLoader->loadGameObject(parent).transform);
    GridSquare & g = grid->getActiveGridSquareFromLocalCoords(grid->getGridPosition(t.position));
    t.move(g.pathVector);
}
