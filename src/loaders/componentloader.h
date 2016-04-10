#ifndef COMPONENTLOADER_H
#define COMPONENTLOADER_H

#include<collisionengine.h>
#include<inputengine.h>
#include<transformengine.h>
#include<physicsengine.h>
#include<logicengine.h>
#include<renderengine.h>

namespace BQ{

class EventEngine;
class GameLogic;
class GameObjectLoader;

typedef std::map<std::string, int>::iterator it;

class ComponentLoader
{
public:
    ComponentLoader();

    Transform & getTransform(int);
    Collidable & getCollidable(int);
    RigidBody & getRigidBody(int);
    GameLogic & getGameLogic(int);
    Behaviour & getBehaviour(int);

    Collidable & getCollidableFromObject(GameObject&,std::string);

    std::vector<int> getComponentsFromObject(GameObject &, std::string);

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

    EventEngine *getEventEngine() const;
    void setEventEngine(EventEngine *value);

    GameObjectLoader *getGameObjectLoader() const;
    void setGameObjectLoader(GameObjectLoader *value);

    LogicEngine *getLogicEngine() const;
    void setLogicEngine(LogicEngine *value);

    RenderEngine *getRenderEngine() const;
    void setRenderEngine(RenderEngine *value);

private:

    GameObjectLoader * gameObjectLoader;

    CollisionEngine* collisionEngine;
    InputEngine* inputEngine;
    TransformEngine* transformEngine;
    PhysicsEngine* physicsEngine;
    EventEngine* eventEngine;
    LogicEngine* logicEngine;
    RenderEngine* renderEngine;
};
}

#endif // COMPONENTLOADER_H
