#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <factory.h>
#include <component.h>
#include <transform.h>
#include <gameobject.h>

#include <transformengine.h>


using namespace BQ;

class ComponentFactory : public Factory
{
public:
    ComponentFactory();

    Transform* newTransform();
    Transform* newTransform(std::string);
    Transform* newChildTransform(Transform*);

    TransformEngine *getTransformEngine() const;
    void setTransformEngine(TransformEngine *value);

private:

    TransformEngine* transformEngine;

};

#endif // COMPONENTFACTORY_H
