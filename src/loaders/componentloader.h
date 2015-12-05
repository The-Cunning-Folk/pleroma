#ifndef COMPONENTLOADER_H
#define COMPONENTLOADER_H

#include<collisionengine.h>
#include<inputengine.h>
#include<transformengine.h>
namespace BQ{
class ComponentLoader
{
public:
    ComponentLoader();

    Transform & getTransform(int);

    CollisionEngine *getCollisionEngine() const;
    void setCollisionEngine(CollisionEngine *value);

    InputEngine *getInputEngine() const;
    void setInputEngine(InputEngine *value);



    TransformEngine *getTransformEngine() const;
    void setTransformEngine(TransformEngine *value);

private:

    CollisionEngine* collisionEngine;
    InputEngine* inputEngine;
    TransformEngine* transformEngine;
};
}

#endif // COMPONENTLOADER_H
