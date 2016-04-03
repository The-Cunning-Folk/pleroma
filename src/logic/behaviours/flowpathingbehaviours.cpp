#include "flowpathingbehaviours.h"

#include <gameobject.h>
#include<componentloader.h>
#include<gameobjectloader.h>


using namespace BQ;

FlowPathingBehaviours::FlowPathingBehaviours()
{
    pathSpeed=100;
    path = false;
    targetProximity = 64;
}


void FlowPathingBehaviours::collisionWith(BQ::GameObject & o, std::string ca, std::string cb)
{

}

void FlowPathingBehaviours::beforeEvents()
{

}

void FlowPathingBehaviours::resolveEvent(Event & e)
{
    if(compare(e.parsedScript["action"],"ray_target_impact"))
    {
        path = true;
        Transform & target = gameObjectLoader->loadGameObject(e.parsedScript["val"]).loadTransform();
        Transform & me = componentLoader->getTransform( gameObjectLoader->loadGameObject(parent).transform);
        if(maths->mag(target.position - me.position) < targetProximity)
        {
            path = false;
        }

    }
}


void FlowPathingBehaviours::update()
{

    if(path)
    {
        Transform & t = componentLoader->getTransform( gameObjectLoader->loadGameObject(parent).transform);
        sf::Vector2i gPos = grid->getGridPosition(t.position);
        GridSquare & g = grid->getActiveGridSquareFromGlobalCoords(gPos);
        t.velocity += pathSpeed*maths->unit(g.pathVector);
    }

    //t.move(delta*pathSpeed*maths->unit(g.pathVector));
}
