#include "game.h"

using namespace BQ;

Game::Game()
{

}

void Game::runTests()
{
    //add temporary stuff here for testing and debugging so the loop doesn't get too cluttered
    if(input.keyToggled("addObject"))
        gameObjectFactory.newCollisionObject();


}

void Game::runEngines()
{

    GameObject & player = gameObjectLoader.loadGameObject("player_1");
    GameObject & testObj = gameObjectLoader.loadGameObject("testpather");

    inputEngine.run();


    grid.setActiveBounds(transformEngine.bounds);




    float deltaT = debug->time.getSeconds("logicTime");
    viewPort.update();
    transformEngine.setBounds(viewPort.renderRegion);
    transformEngine.setDelta(deltaT);
    transformEngine.run();


    occlusionManager.setActiveObjects(transformEngine.getObjectsInRange());

    collisionEngine.setActiveComponents(occlusionManager.getActiveComponents("collidable"));
    physicsEngine.setActiveComponents(occlusionManager.getActiveComponents("rigidbody"));
    eventEngine.setActiveComponents(occlusionManager.getActiveComponents("gamelogic"));
    rayCastingEngine.setActiveComponents(occlusionManager.getActiveComponents("rayemitter"));

    //float logicTime = debug->time.getSeconds("logicTime");
    //eventEngine.setDelta(logicTime);

    collisionEngine.quadtree.setRegion(viewPort.renderRegion);
    collisionEngine.start();
    collisionEngine.run();

    physicsEngine.setDelta(deltaT);
    physicsEngine.run();

    rayCastingEngine.start();

    sf::Vector2f pPos = player.loadTransform().position;

    rayCastingEngine.createTargettedRay(player,testObj);

    rayCastingEngine.run();

    pathingEngine.addGoal(player.loadTransform().position);
    pathingEngine.run();



    eventEngine.run();

    debugDisplayEngine.run();


    viewPort.update();
    deltaT = debug->time.getSeconds("logicTime");
    transformEngine.setDelta(deltaT);
    transformEngine.updatePositions();



}

void Game::run()
{
    if(debug == NULL){
        std::cout << "no debug instance present" << std::endl;
        return;
    }

    if(gameWindow == NULL){
        debug->println("no game window defined, the application will now exit");
        return;
    }


    initialiseInjections(); //injections
    initialiseInput();
    initialiseClocks(); //clock definitions

    initialiseTests();

    initialisePlayers();

    DebugUtils& print = *debug;

    print.println("starting game loop");

    GameWindow& window = *gameWindow;

    sf::Text fpsDisplay;
    fpsDisplay.setPosition(15,15);
    fpsDisplay.setCharacterSize(20);
    fpsDisplay.setFont(resourceLoader.getFont("8bit16.ttf"));

    bool transformDebug = true;
    bool collisionDebug = true;
    bool fpsDebug = true;
    bool pathingDebug = false;
    bool raycastingDebug = true;



    //end temporary behaviours

    while(window.isOpen()){
        //game loop goes here


        window.updateEvents();

        //get time since last window.clear call
        //logictime is for calculating how long it's been since the engines were last updated

        //logic here

        input.update();

        if(input.keyToggled("debug"))
            fpsDebug = !fpsDebug;

        if(input.keyToggled("transformDebug"))
            transformDebug = !transformDebug;

        if(input.keyToggled("collisionDebug"))
            collisionDebug = !collisionDebug;

        if(input.keyToggled("pathingDebug"))
            pathingDebug = !pathingDebug;

        if(input.keyToggled("raycastingDebug"))
            raycastingDebug = !raycastingDebug;

        //temporary behaviours

        runTests();

        runEngines();

        //end logic

        //restart the logic timer
        print.time.restartClock("logicTime");

        window.clear();

        //drawing here

        window.window.setView(viewPort.view);

        if(transformDebug)
            transformEngine.drawDebug();

        if(collisionDebug)
            collisionEngine.drawDebug();

        if(pathingDebug)
            pathingEngine.drawDebug();

        if(raycastingDebug)
            rayCastingEngine.drawDebug();


        //get the default viewport back
        window.window.setView(window.window.getDefaultView());

        //draw HUD stuff here

        debugDisplayEngine.drawDebug();

        //end drawing

        //framerate stuff
        float frameTime = print.time.getSeconds("frameTime");
        stabiliseFrameRate(frameTime);
        frameTime = print.time.getSecondsAndRestart("frameTime");
        float fps = 1.0/frameTime;

        fpsDisplay.setString(std::to_string(math.roundAndCast(fps)));

        //end framerate stuff

        if(fpsDebug)
            window.draw(fpsDisplay);

        window.display();



    }
}

void Game::initialiseInjections()
{
   debug->println("injecting dependencies");

   occlusionManager.setGame(this);
   occlusionManager.setComponentLoader(&componentLoader);
   occlusionManager.setGameObjectLoader(&gameObjectLoader);

   viewPort.setComponentLoader(&componentLoader);
   viewPort.setMaths(&math);

   resourceLoader.setDebug(debug);

   gameObjectLoader.setGameObjects(&gameObjects);

   componentLoader.setGameObjectLoader(&gameObjectLoader);
   componentLoader.setTransformEngine(&transformEngine);
   componentLoader.setCollisionEngine(&collisionEngine);
   componentLoader.setPhysicsEngine(&physicsEngine);
   componentLoader.setEventEngine(&eventEngine);
   componentLoader.setLogicEngine(&logicEngine);

   componentFactory.setCollisionEngine(&collisionEngine);
   componentFactory.setTransformEngine(&transformEngine);
   componentFactory.setInputEngine(&inputEngine);
   componentFactory.setEventEngine(&eventEngine);
   componentFactory.setCollisionEngine(&collisionEngine);
   componentFactory.setPhysicsEngine(&physicsEngine);
   componentFactory.setComponentLoader(&componentLoader);
   componentFactory.setGrid(&grid);
   componentFactory.setGameObjectLoader(&gameObjectLoader);
   componentFactory.setLogicEngine(&logicEngine);
   componentFactory.setRayCastingEngine(&rayCastingEngine);

   gameObjectFactory.setStack(&gameObjects);
   gameObjectFactory.setComponentFactory(&componentFactory);

   physicsEventFactory.setPhysicsEngine(&physicsEngine);
   eventFactory.setEventEngine(&eventEngine);
   inputFactory.setInputEngine(&inputEngine);

   gameObjects.setComponentLoader(&componentLoader);

   grid.setDebug(debug);

   physicsEngine.setGame(this);
   eventEngine.setGame(this);
   inputEngine.setGame(this);
   transformEngine.setGame(this);
   collisionEngine.setGame(this);
   debugDisplayEngine.setGame(this);
   pathingEngine.setGame(this);
   logicEngine.setGame(this);
   rayCastingEngine.setGame(this);

   componentFactory.setGame(this);
   gameObjectFactory.setGame(this);
   eventFactory.setGame(this);
   inputFactory.setGame(this);
   physicsEventFactory.setGame(this);
}

void Game::initialiseClocks()
{
    debug->time.addClock("frameTime");
    debug->time.addClock("logicTime");
}

void Game::initialiseInput()
{
    debug->println("initialising global inputs");
    input.setKeyInput("menu",sf::Keyboard::Escape);
    input.setKeyInput("debug",sf::Keyboard::F3);
    input.setKeyInput("transformDebug",sf::Keyboard::F4);
    input.setKeyInput("collisionDebug",sf::Keyboard::F5);
    input.setKeyInput("pathingDebug",sf::Keyboard::F6);
    input.setKeyInput("raycastingDebug",sf::Keyboard::F7);

}

void Game::initialiseTests()
{
    debug->println("setting up tests");
    input.setKeyInput("addObject",sf::Keyboard::F8);

    //for testing only
    transformEngine.setWrapAround(false);
    debug->println(std::to_string(gameWindow->getWidth()));

    //remove later!

    //GameObject& coll = gameObjectFactory.newPathingObject();


    for(int i=1; i<=100; i++)
    {
        for(int j=1; j<=100; j++)
        {
            int spinner = math.randomInt(0,20);
            if(spinner <= 2)
            {
                GameObject& coll = gameObjectFactory.newImmovableObject();
                coll.loadTransform().setPosition(sf::Vector2f(i*32 - 1280,j*32-1280));
                if(math.randomInt(0,2) == 1)
                {
                    componentLoader.getCollidableFromObject(coll,"hitbox").immovable = false;
                }
            }
            else if(spinner == 9)
            {
                GameObject& coll = gameObjectFactory.newPathingObject();
                coll.loadTransform().setPosition(sf::Vector2f(i*32 - 1280,j*32-1280));
            }

        }
    }
    GameObject& coll = gameObjectFactory.newPathingObject("testpather");
    coll.loadTransform().setPosition(sf::Vector2f(164,128));
}

void Game::initialisePlayers()
{
    inputFactory.detectControllers();
    debug->println("adding players");
    GameObject& player = gameObjectFactory.newPlayerObject();
    viewPort.focusedTransform =  player.getTransform();
}

void Game::stabiliseFrameRate(float currentFrameDuration)
{
    sf::Time sleepTime = sf::seconds(targetFrameDuration - currentFrameDuration);
    if(sleepTime.asSeconds() < 0){

        std::string targetString = std::to_string(targetFrameDuration);
        std::string currentString = std::to_string(currentFrameDuration);

        std::string warning = "frame duration exceeded target";
        //debug->printwarn(warning);
    }
    sf::sleep(sleepTime);
}

void Game::setDebug(DebugUtils *value)
{
    debug = value;
}

TransformEngine Game::getTransformEngine() const
{
    return transformEngine;
}

void Game::setTransformEngine(const TransformEngine &value)
{
    transformEngine = value;
}

InputEngine Game::getInputEngine() const
{
    return inputEngine;
}

void Game::setInputEngine(const InputEngine &value)
{
    inputEngine = value;
}

EventEngine Game::getEventEngine() const
{
    return eventEngine;
}

void Game::setEventEngine(const EventEngine &value)
{
    eventEngine = value;
}

CollisionEngine Game::getCollisionEngine() const
{
    return collisionEngine;
}

void Game::setCollisionEngine(const CollisionEngine &value)
{
    collisionEngine = value;
}

DebugDisplayEngine Game::getDebugDisplayEngine() const
{
    return debugDisplayEngine;
}

void Game::setDebugDisplayEngine(const DebugDisplayEngine &value)
{
    debugDisplayEngine = value;
}

PhysicsEngine Game::getPhysicsEngine() const
{
    return physicsEngine;
}

void Game::setPhysicsEngine(const PhysicsEngine &value)
{
    physicsEngine = value;
}

OcclusionManager Game::getOcclusionManager() const
{
    return occlusionManager;
}

void Game::setOcclusionManager(const OcclusionManager &value)
{
    occlusionManager = value;
}

PathingEngine Game::getPathingEngine() const
{
    return pathingEngine;
}

void Game::setPathingEngine(const PathingEngine &value)
{
    pathingEngine = value;
}

Grid Game::getGrid() const
{
    return grid;
}

void Game::setGrid(const Grid &value)
{
    grid = value;
}

RaycastingEngine Game::getRayCastingEngine() const
{
    return rayCastingEngine;
}

void Game::setRayCastingEngine(const RaycastingEngine &value)
{
    rayCastingEngine = value;
}

void Game::setGameWindow(window_ptr window)
{
    gameWindow = window;

}

window_ptr Game::getGameWindow()
{
    return gameWindow;
}

void Game::setFrameRate(float fps)
{
    frameRate = fps;
    targetFrameDuration = 1.0/fps;
}

float Game::getFrameRate()
{
    return (frameRate);
}

