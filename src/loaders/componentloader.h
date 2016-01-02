#ifndef COMPONENTLOADER_H
#define COMPONENTLOADER_H

#include<collisionengine.h>
#include<inputengine.h>
#include<transformengine.h>
#include<physicsengine.h>
namespace BQ{

typedef std::map<std::string, int>::iterator it;

class ComponentLoader
{
public:
    ComponentLoader();

    Transform & getTransform(int);
    Collidable & getCollidable(int);
    RigidBody & getRigidBody(int);

    std::vector<int> getCollidablesFromObject(GameObject & );
    std::vector<int> getGameLogicsFromObject(GameObject & );
    std::vector<int> getInputsFromObject(GameObject & );
    std::vector<int> getRigidBodiesFromObject(GameObject &);

    std::vector<int> getIndicesFromMap(std::map<std::string,int>);

    CollisionEngine *getCollisionEngine() const;
    void setCollisionEngine(CollisionEngine *value);

    InputEngine *getInputEngine() const;
    void setInputEngine(InputEngine *value);

    TransformEngine *getTransformEngine() const;
    void setTransformEngine(TransformEngine *value);

    PhysicsEngine *getPhysicsEngine() const;
    void setPhysicsEngine(PhysicsEngine *value);

private:

    CollisionEngine* collisionEngine;
    InputEngine* inputEngine;
    TransformEngine* transformEngine;
    PhysicsEngine* physicsEngine;
};
}

#endif // COMPONENTLOADER_H
