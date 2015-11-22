#include "componentfactory.h"

ComponentFactory::ComponentFactory()
{

}


BQ::Transform *ComponentFactory::newTransform()
{
    return transformEngine->addTransform();
}

Transform *ComponentFactory::newTransform(std::string name)
{
    Transform* transform = newTransform();
    transform->setName(name);
    return(transform);
}

Transform *ComponentFactory::newChildTransform(Transform* parent)
{
    Transform* transform = newTransform();
    parent->children.push_back(transform);
    return(transform);
}

TransformEngine *ComponentFactory::getTransformEngine() const
{
    return transformEngine;
}

void ComponentFactory::setTransformEngine(TransformEngine *value)
{
    transformEngine = value;
}
