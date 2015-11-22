#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <factory.h>
#include <component.h>
#include <transform.h>

using namespace BQ;

class ComponentFactory : public Factory
{
public:
    ComponentFactory();

    Transform* newTransform();
    Transform* newTransform(std::string);
    Transform* newChildTransform(Transform*);



};

#endif // COMPONENTFACTORY_H
