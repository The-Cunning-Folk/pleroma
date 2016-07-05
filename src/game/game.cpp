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

    viewPort.update();

    GameObject & player = gameObjectLoader.loadGameObject("player_1");

    inputEngine.run();

    float deltaStep = debug->time.getSecondsAndRestart("stepClock");
    transformEngine.setDelta(deltaStep);
    transformEngine.runStep();

    transformEngine.setBounds(viewPort.renderRegion);
    transformEngine.run();

    grid.setActiveBounds(transformEngine.bounds);

    float deltaT = debug->time.getSecondsAndRestart("logicTime");

    occlusionManager.setActiveObjects(transformEngine.getObjectsInRange());

    collisionEngine.setActiveComponents(occlusionManager.getActiveComponents("collidable"));
    physicsEngine.setActiveComponents(occlusionManager.getActiveComponents("rigidbody"));
    eventEngine.setActiveComponents(occlusionManager.getActiveComponents("gamelogic"));
    rayCastingEngine.setActiveComponents(occlusionManager.getActiveComponents("rayemitter"));
    renderEngine.setActiveComponents(occlusionManager.getActiveComponents("spriterenderer"));

    //float logicTime = debug->time.getSeconds("logicTime");
    //eventEngine.setDelta(logicTime);

    collisionEngine.quadtree.setRegion(viewPort.renderRegion);
    collisionEngine.start();
    collisionEngine.run();

    physicsEngine.setDelta(deltaT);
    physicsEngine.run();

    rayCastingEngine.start();
    rayCastingEngine.run();

    pathingEngine.addGoal(player.loadTransform().position);
    pathingEngine.run();


    eventEngine.start();
    eventEngine.run();

    transformEngine.runCorrections();

    renderEngine.start();
    renderEngine.run();

    debugDisplayEngine.run();

    transformEngine.finish();
    eventEngine.finish();
    collisionEngine.finish();
    pathingEngine.finish();
    rayCastingEngine.finish();
    renderEngine.finish();

    viewPort.update();

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
    initialiseEnvironment();

    initialiseTests();
    initialisePlayers();

    DebugUtils& print = *debug;

    print.println("starting game loop");

    GameWindow& window = *gameWindow;

    sf::Text fpsDisplay;
    fpsDisplay.setPosition(15,15);
    fpsDisplay.setCharacterSize(16);
    fpsDisplay.setFont(resourceLoader.getFont("8bit16.ttf"));

    sf::Text posDisplay;
    posDisplay.setPosition(15,32);
    posDisplay.setCharacterSize(16);
    posDisplay.setFont(resourceLoader.getFont("8bit16.ttf"));


    bool transformDebug = false;
    bool collisionDebug = false;
    bool fpsDebug = true;
    bool pathingDebug = false;
    bool raycastingDebug = false;



    //end temporary behaviours
    transformEngine.wake();
    collisionEngine.wake();
    renderEngine.wake();

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



        window.clear();

        //drawing here

        window.window.setView(viewPort.view);

        if(transformDebug)
            transformEngine.drawDebug();

        renderEngine.drawDebug();

        if(collisionDebug)
            collisionEngine.drawDebug();

        if(pathingDebug)
            pathingEngine.drawDebug();

        if(raycastingDebug)
            rayCastingEngine.drawDebug();

        std::string winPosStr = "w_pos - " + debug->formatVector(window.window.getView().getCenter(),1);


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

        fpsDisplay.setString(std::to_string(math.roundAndCast(fps)) + "  -  " + std::to_string(math.roundAndCast(frameTime*1000)));

        posDisplay.setString(winPosStr);

        //end framerate stuff

        if(fpsDebug)
        {
            window.draw(fpsDisplay);
            window.draw(posDisplay);
        }

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

   //component loader injections

   componentLoader.setGameObjectLoader(&gameObjectLoader);

   componentLoader.setTransformEngine(&transformEngine);
   componentLoader.setCollisionEngine(&collisionEngine);
   componentLoader.setPhysicsEngine(&physicsEngine);
   componentLoader.setEventEngine(&eventEngine);
   componentLoader.setLogicEngine(&logicEngine);
   componentLoader.setRenderEngine(&renderEngine);
   componentLoader.setRayCastingEngines(&rayCastingEngine);

   //end of component loader injections

   //component factory injections

   componentFactory.setGrid(&grid);
   componentFactory.setComponentLoader(&componentLoader);
   componentFactory.setGameObjectLoader(&gameObjectLoader);

   componentFactory.setCollisionEngine(&collisionEngine);
   componentFactory.setTransformEngine(&transformEngine);
   componentFactory.setInputEngine(&inputEngine);
   componentFactory.setEventEngine(&eventEngine);
   componentFactory.setCollisionEngine(&collisionEngine);
   componentFactory.setPhysicsEngine(&physicsEngine);
   componentFactory.setLogicEngine(&logicEngine);
   componentFactory.setRayCastingEngine(&rayCastingEngine);
   componentFactory.setRenderEngine(&renderEngine);

   //end of component factory injections

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
   renderEngine.setGame(this);

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
    debug->time.addClock("stepClock");
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


    for(int i=1; i<=50; i++)
    {
        for(int j=1; j<=50; j++)
        {
            int spinner = math.randomInt(0,50);
            if(spinner <= 10)
            {
                GameObject& coll = gameObjectFactory.newImmovableObject();
                coll.loadTransform().setPosition(sf::Vector2f(i*64+math.randomInt(-16,16) - 1280,j*64+math.randomInt(-16,16)-1280));
                if(math.randomInt(0,2) == 1)
                {
                    //componentLoader.getCollidableFromObject(coll,"hitbox").immovable = false;
                    //componentLoader.getSpriteRendererFromObject(coll,"sprite").textureRect = sf::IntRect(96,0,32,64);
                }
            }
            else if(spinner > 45)
            {
                GameObject& coll = gameObjectFactory.newPathingObject();
                coll.loadTransform().setPosition(sf::Vector2f(i*64 - 1280,j*64-1280));
            }

        }
    }
}

void Game::initialisePlayers()
{
    inputFactory.detectControllers();
    debug->println("adding players");
    GameObject& player = gameObjectFactory.newPlayerObject();
    viewPort.focusedTransform =  player.getTransform();
}

void Game::initialiseEnvironment()
{
    rapidjson::Document levelConfig = resourceLoader.loadJsonFile("config/levels.json");
    assert(levelConfig["parentdirectory"].IsString());
    assert(levelConfig["levels"].IsArray());

    std::string lDir = levelConfig["parentdirectory"].GetString();
    const rapidjson::Value & files = levelConfig["levels"];
    assert(files.IsArray());

    for (rapidjson::SizeType i = 0; i < files.Size(); i++)
    {
        Level lvl;
        debug->println(lDir + "/" + files[i].GetString());
        rapidjson::Document levelJson = resourceLoader.loadJsonFile(lDir + "/" + files[i].GetString());

        assert(levelJson["name"].IsString());
        assert(levelJson["ground"].IsObject());

        std::string levelName = levelJson["name"].GetString();
        rapidjson::Value ground = levelJson["ground"].GetObject();

        assert(ground["default_sheet"].IsString());

        Tile defaultTile;

        defaultTile.index = ground["default_tile"].GetInt();

        lvl.tileMap.tileset = ground["default_sheet"].GetString();
        lvl.tileMap.defaultTile = defaultTile;

        lvl.tileMap.tileLayers.resize(ground["layers"].GetArray().Size());

        assert(ground["layers"].IsArray());

        for(rapidjson::SizeType lnum = 0; lnum<ground["layers"].Size(); lnum++)
        {
            TileLayer & layer = lvl.tileMap.tileLayers[lnum];
            rapidjson::Value layerJson = ground["layers"][lnum].GetObject();

            if(layerJson.HasMember("sheet"))
            {
                layer.tileset = layerJson["sheet"].GetString();
            }
            else
            {
                layer.tileset = ground["default_sheet"].GetString();
            }
            if(layerJson.HasMember("default"))
            {
                layer.defaultTile.index = layerJson["default"].GetInt();
            }
            else if(lnum == 0)
            {
                layer.defaultTile = defaultTile;
            }

            assert(layerJson["map"].IsArray());

            for(rapidjson::SizeType j=0; j<layerJson["map"].Size();j++)
            {
                Tile tile;
                rapidjson::Value tileJson = layerJson["map"][j].GetObject();
                int sheetIndex = tileJson["tile"].GetInt();
                int xpos = tileJson["x"].GetInt();
                int ypos = tileJson["y"].GetInt();
                int rot = tileJson["rot"].GetInt();
                bool flipX = tileJson["flipX"].GetBool();
                tile.index = sheetIndex;
                tile.x = xpos;
                tile.y = ypos;
                tile.rot = rot;
                tile.flipX = flipX;
                layer.tiles[xpos][ypos] = tile;
            }

        }

        levels[levelName] = lvl;
    }

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

