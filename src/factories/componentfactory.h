#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <factory.h>
#include <component.h>
#include <transform.h>
#include <gameobject.h>

#include <transformengine.h>
#include <inputengine.h>


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

    TransformEngine *getTransformEngine() const;
    void setTransformEngine(TransformEngine *value);

    InputEngine *getInputEngine() const;
    void setInputEngine(InputEngine *value);

private:

    TransformEngine* transformEngine;
    InputEngine* inputEngine;

};

#endif // COMPONENTFACTORY_H
