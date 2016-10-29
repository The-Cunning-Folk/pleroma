#ifndef GAME_H
#define GAME_H

#include <SFML/System/Sleep.hpp>
#include <memory>
#include <gamewindow.h>
#include <debugutils.h>
#include <mathsutils.h>

#include<grid.h>
#include<inputmap.h>
#include<viewport.h>

#include<level.h>

#include<gameobjectstore.h>

#include<gameobjectfactory.h>
#include<eventfactory.h>
#include<componentfactory.h>
#include<inputfactory.h>

#include<transformengine.h>
#include<eventengine.h>
#include<collisionengine.h>
#include<debugdisplayengine.h>
#include<physicsengine.h>
#include<pathingengine.h>
#include<logicengine.h>
#include<raycastingengine.h>
#include<renderengine.h>

#include<componentloader.h>
#include<resourceloader.h>
#include<gameobjectloader.h>

#include<datafileparser.h>
#include<luacontroller.h>
#include<occlusionmanager.h>



typedef std::shared_ptr<BQ::GameWindow> window_ptr;

namespace BQ
{
class Game
{
public:
    Game();

    void setGameWindow(window_ptr);
    window_ptr getGameWindow();

    std::map<std::string,Level> levels;
    std::map<std::string,GameObjectPattern> entities;

    void changeLevel(std::string);

    std::string currentLevel;

    float delta;

    Level & getCurrentLevel();

    void setFrameRate(float);
    float getFrameRate();

    void stabiliseFrameRate(float);

    void run();

    void printObjectDebug();
    void initialiseInjections();
    void initialiseClocks();
    void initialiseInput();
    void initialisePlayers();
    void initialiseEnvironment();
    void initialiseTests();
    void runTests();
    void runEngines();

    void setDebug(DebugUtils *value);

    //loaders
    ComponentLoader componentLoader;
    ResourceLoader resourceLoader;
    GameObjectLoader gameObjectLoader;

    DataFileParser dataFileParser;

    GameObjectFactory gameObjectFactory;
    ComponentFactory componentFactory;
    EventFactory eventFactory;
    InputFactory inputFactory;

    LuaController luaCtrl;

    //inherited properties
    DebugUtils* debug;
    window_ptr gameWindow;

    //utilities owned by game
    MathsUtils math;

    TransformEngine getTransformEngine() const;
    void setTransformEngine(const TransformEngine &value);

    InputEngine getInputEngine() const;
    void setInputEngine(const InputEngine &value);

    EventEngine getEventEngine() const;
    void setEventEngine(const EventEngine &value);

    CollisionEngine getCollisionEngine() const;
    void setCollisionEngine(const CollisionEngine &value);

    DebugDisplayEngine getDebugDisplayEngine() const;
    void setDebugDisplayEngine(const DebugDisplayEngine &value);

    PhysicsEngine getPhysicsEngine() const;
    void setPhysicsEngine(const PhysicsEngine &value);

    OcclusionManager getOcclusionManager() const;
    void setOcclusionManager(const OcclusionManager &value);

    PathingEngine getPathingEngine() const;
    void setPathingEngine(const PathingEngine &value);

    Grid getGrid() const;
    void setGrid(const Grid &value);

    Grid grid;

    RaycastingEngine getRayCastingEngine() const;
    void setRayCastingEngine(const RaycastingEngine &value);

    //engines
    TransformEngine transformEngine;
    InputEngine inputEngine;
    EventEngine eventEngine;
    CollisionEngine collisionEngine;
    DebugDisplayEngine debugDisplayEngine;
    PhysicsEngine physicsEngine;
    PathingEngine pathingEngine;
    LogicEngine logicEngine;
    RaycastingEngine rayCastingEngine;
    RenderEngine renderEngine;

private:

    //managers
    OcclusionManager occlusionManager;

    //factories





    //global properties

    InputMap input;

    //variables
    float frameRate;
    float targetFrameDuration;


};
}
#endif // GAME_H
