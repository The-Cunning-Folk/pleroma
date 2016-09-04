#include "flowpathingbehaviours.h"

#include <gameobject.h>
#include <game.h>

using namespace BQ;

FlowPathingBehaviours::FlowPathingBehaviours()
{
    pathSpeed=70;
    path = true;
    targetProximity = 32 + rand()%32;
    active = false;

}


void FlowPathingBehaviours::collisionWith(BQ::GameObject & o, std::string ca, std::string cb)
{

}

void FlowPathingBehaviours::beforeEvents()
{
    hasLOS = false;
}

void FlowPathingBehaviours::resolveEvent(Event & e)
{
    if(compare(e.parsedScript["action"],"ray_target_impact"))
    {
        target = (e.parsedScript["val"]);
        hasLOS = true;
        active = true;
    }
}


void FlowPathingBehaviours::update()
{
    Grid & grid = game->grid;
    ComponentLoader & componentLoader = game->componentLoader;
    GameObjectLoader & gameObjectLoader = game->gameObjectLoader;
    MathsUtils & maths = game->math;

    if(path && !hasLOS && active)
    {
        Transform & t = componentLoader.getTransform( gameObjectLoader.loadGameObject(parent).transform);
        sf::Vector2i gPos = grid.getGridPosition(t.position);
        GridSquare & g = grid.getActiveGridSquareFromGlobalCoords(gPos);

        t.velocity += pathSpeed*maths.unit(g.pathVector);
    }
    else if(path && hasLOS & active)
    {

        Transform & tar = componentLoader.getTransform(gameObjectLoader.loadGameObject(target).transform);
        Transform & me = componentLoader.getTransform( gameObjectLoader.loadGameObject(parent).transform);
        float prox = maths.mag(tar.position - me.position);
        if(prox > targetProximity)
        {
            me.velocity += pathSpeed*maths.unit(tar.position - me.position);
        }
        else
        {
            path = false;
        }
    }
    if(!path && active)
    {

        Transform & tar = componentLoader.getTransform( gameObjectLoader.loadGameObject(target).transform);
        Transform & me = componentLoader.getTransform( gameObjectLoader.loadGameObject(parent).transform);
        float prox = maths.mag(tar.position - me.position);
        if(prox > 2*targetProximity)
        {
            path = true;
        }
        else if(prox < 0.5*targetProximity)
        {
            me.velocity -= pathSpeed*maths.unit(tar.position - me.position);
        }
        else
        {

            sf::Vector2f norm = pathSpeed*maths.unitNormal(tar.position - me.position);
            me.velocity += norm;
        }
    }

    //t.move(delta*pathSpeed*maths->unit(g.pathVector));
}
