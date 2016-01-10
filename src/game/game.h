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

#include<gameobjectstack.h>

#include<gameobjectfactory.h>
#include<eventfactory.h>
#include<componentfactory.h>
#include<inputfactory.h>
#include<physicseventfactory.h>

#include<transformengine.h>
#include<eventengine.h>
#include<collisionengine.h>
#include<debugdisplayengine.h>
#include<physicsengine.h>

#include<componentloader.h>
#include<resourceloader.h>
#include<gameobjectloader.h>

typedef std::shared_ptr<BQ::GameWindow> window_ptr;

namespace BQ
{
class Game
{
public:
    Game();

    void setGameWindow(window_ptr);
    window_ptr getGameWindow();

    void setFrameRate(float);
    float getFrameRate();

    void stabiliseFrameRate(float);

    void run();

    void initialiseInjections();
    void initialiseClocks();
    void initialiseInput();
    void initialiseTests();
    void initialisePlayers();

    void runTests();
    void runEngines();

    void setDebug(DebugUtils *value);

    GameObjectStack gameObjects;

    //loaders
    ComponentLoader componentLoader;
    ResourceLoader resourceLoader;
    GameObjectLoader gameObjectLoader;

    GameObjectFactory gameObjectFactory;
    ComponentFactory componentFactory;
    EventFactory eventFactory;
    InputFactory inputFactory;
    PhysicsEventFactory physicsEventFactory;


    //inherited properties
    DebugUtils* debug;
    window_ptr gameWindow;

    //utilities owned by game
    MathsUtils math;

private:



    //factories


    //engines
    TransformEngine transformEngine;
    InputEngine inputEngine;
    EventEngine eventEngine;
    CollisionEngine collisionEngine;
    DebugDisplayEngine debugDisplayEngine;
    PhysicsEngine physicsEngine;



    //global properties
    Grid grid;
    InputMap input;
    ViewPort viewPort;

    //variables
    float frameRate;
    float targetFrameDuration;


};
}
#endif // GAME_H
