#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <factory.h>
#include <component.h>
#include <transform.h>
#include <gameobject.h>

#include <transformengine.h>
#include <inputengine.h>
#include <eventengine.h>
#include <collisionengine.h>

using namespace BQ;

class ComponentFactory : public Factory
{
public:
    ComponentFactory();

    Transform* newTransform();
    Transform* newTransform(std::string);
    Transform* newChildTransform(Transform*);

    PlayerInput* newPlayerInput();
    PlayerInput* newPlayerInput(std::string);

    GameLogic* newGameLogic();
    GameLogic* newGameLogic(std::string);

    Collidable* newCollidable();
    Collidable* newCollidable(std::string);

    TransformEngine *getTransformEngine() const;
    void setTransformEngine(TransformEngine *value);

    InputEngine *getInputEngine() const;
    void setInputEngine(InputEngine *value);

    EventEngine *getEventEngine() const;
    void setEventEngine(EventEngine *value);

    CollisionEngine *getCollisionEngine() const;
    void setCollisionEngine(CollisionEngine *value);

private:

    TransformEngine* transformEngine;
    InputEngine* inputEngine;
    EventEngine* eventEngine;
    CollisionEngine* collisionEngine;
};

#endif // COMPONENTFACTORY_H
