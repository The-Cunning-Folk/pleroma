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

PlayerInput *ComponentFactory::newPlayerInput()
{
    return inputEngine->addPlayerInput();
}

PlayerInput *ComponentFactory::newPlayerInput(std::string name)
{
    PlayerInput* input = newPlayerInput();
    input->setName(name);
    return(input);
}

TransformEngine *ComponentFactory::getTransformEngine() const
{
    return transformEngine;
}

void ComponentFactory::setTransformEngine(TransformEngine *value)
{
    transformEngine = value;
}

InputEngine *ComponentFactory::getInputEngine() const
{
    return inputEngine;
}

void ComponentFactory::setInputEngine(InputEngine *value)
{
    inputEngine = value;
}
