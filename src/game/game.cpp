#include "game.h"

using namespace BQ;

Game::Game()
{
    delta = 0;
}

void Game::runTests()
{
    //add temporary stuff here for testing and debugging so the loop doesn't get too cluttered
    if(input.keyToggled("changeScene"))
    {
        if(currentLevel == "butterfly_demo")
        {
            changeLevel("qa_space");
        }
        else
        {
            changeLevel("butterfly_demo");
        }
    }

}

void Game::startEngines()
{

}

void Game::runEngines()
{

    ViewPort & viewPort = gameWindow->primaryView;

    GameObject & player = gameObjectLoader.loadGameObject("player_1");


    inputEngine.run();

    delta = debug->time.getSecondsAndRestart("stepClock");
    transformEngine.setDelta(delta);
    transformEngine.runStep();

    transformEngine.setBounds(viewPort.renderRegion);
    transformEngine.run();

    grid.setActiveBounds(transformEngine.bounds);
    renderEngine.setVisibleRegion(viewPort.drawRegion);

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

    rayCastingEngine.start();
    rayCastingEngine.run();

    pathingEngine.addGoal(componentLoader.getTransform(player.transform).position);
    pathingEngine.run();

    eventEngine.start();
    eventEngine.run();

    physicsEngine.setDelta(deltaT);
    physicsEngine.run();

    transformEngine.runCorrections();

    renderEngine.start();
    renderEngine.run();



    debugDisplayEngine.run();


}

void Game::finishEngines()
{
    transformEngine.finish();
    eventEngine.finish();
    collisionEngine.finish();
    physicsEngine.finish();
    pathingEngine.finish();
    rayCastingEngine.finish();
    renderEngine.finish();

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

    ViewPort & viewPort = gameWindow->primaryView;

    initialiseInjections(); //injections
    initialiseInput();
    initialiseClocks(); //clock definitions
    initialiseEnvironment();
    initialisePlayers();
    initialiseTests();


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
    bool fpsDebug = false;
    bool objectDebug = false;
    bool pathingDebug = false;
    bool raycastingDebug = false;
    bool runDebugScript = false;
    bool eventDebug = false;

    viewPort.focus();


    //end temporary behaviours

    transformEngine.wake();
    collisionEngine.load();
    collisionEngine.wake();
    renderEngine.load();
    renderEngine.wake();

    rapidjson::Document bconfig = resourceLoader.loadJsonFile("config/scripts.json");

    assert(bconfig["parentdirectory"].IsString());
    std::string bDir = bconfig["parentdirectory"].GetString();

    //load the scripts array
    const rapidjson::Value & files = bconfig["scripts"];
    assert(files.IsArray());

    for (rapidjson::SizeType i = 0; i < files.Size(); i++)
    {
        std::string fileName = files[i].GetString();
        debug->println(resourceLoader.baseDirectory + "/" + bDir + "/" + fileName);
        luaCtrl.script_file(resourceLoader.baseDirectory + "/" + bDir + "/" + fileName);
    }

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

        if(input.keyToggled("objectDebug"))
            objectDebug = !objectDebug;

        if(input.keyToggled("runDebugScript"))
            runDebugScript = !runDebugScript;

        if(input.keyToggled("eventDebug"))
            eventDebug = !eventDebug;
        //temporary behaviours

        runTests();
        viewPort.update();
        runEngines();
        viewPort.update();
        //end logic




        window.clear();

        //drawing here

        window.window.setView(viewPort.view);

        renderEngine.drawDebug();

        if(transformDebug)
            transformEngine.drawDebug();

        if(collisionDebug)
            collisionEngine.drawDebug();

        if(pathingDebug)
            pathingEngine.drawDebug();

        if(raycastingDebug)
            rayCastingEngine.drawDebug();

        if(eventDebug)
            eventEngine.drawDebug();

        if(objectDebug)
            printObjectDebug();

        if(runDebugScript)
        {
            sol::load_result debugScript = resourceLoader.loadLuaScript(luaCtrl,"debug.lua");
            debugScript();
        }


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

        sol::load_result mainScript = resourceLoader.loadLuaScript(luaCtrl,"main.lua");
        mainScript();

        window.display();

        finishEngines();


    }
}

void Game::printObjectDebug()
{
    GameObjectStore & store = getCurrentLevel().objects;
    for(it_object it = store.objects.begin(); it != store.objects.end(); it++) {
        GameObject & g = it->second;
        debug->println(" --- " + g.name + " --- ");
        for(it_complist itl = g.components.begin(); itl != g.components.end() ; itl++)
        {
            debug->println("    [" + itl->first + "]");
            std::map<std::string,int> & m = itl->second;
            for(it_component itc = m.begin(); itc != m.end() ; itc++)
            {
                debug->println("        " + itc->first + ": " + std::to_string(itc->second));
            }

        }
        debug->println("    ------ ");
    }
//        debug->println("--- sprite renderers ---");
//        for(it_sprrenderer it = store.spriteRenderers.begin(); it != store.spriteRenderers.end(); it++) {
//            debug->println(std::to_string(it->first) + ": " + it->second.name + ", " + it->second.getParent());
//        }
//        debug->println("--- collidables ---");
//        for(it_collidable it = store.collidables.begin(); it != store.collidables.end(); it++) {
//            debug->println(std::to_string(it->first) + ": " + it->second.name + ", " + it->second.getParent());
//            debug->println("    points:" + std::to_string(it->second.polygon.points.size()));
//            debug->println("    position:" +
//                           std::to_string(store.transforms[it->second.transform].position.x) +
//                            ", " +
//                           std::to_string(store.transforms[it->second.transform].position.y));
//        }
}

void Game::initialiseInjections()
{
    currentLevel="butterfly_demo";
    ViewPort & viewPort = gameWindow->primaryView;
    debug->println("injecting dependencies");

    luaCtrl.setGame(this);

    occlusionManager.setGame(this);
    occlusionManager.setComponentLoader(&componentLoader);
    occlusionManager.setGameObjectLoader(&gameObjectLoader);

    viewPort.setComponentLoader(&componentLoader);
    viewPort.setMaths(&math);

    resourceLoader.setDebug(debug);
    resourceLoader.loadConfig("var/config.json");

    gameObjectLoader.setGameObjects(&getCurrentLevel().objects);

    //component loader injections

    componentLoader.setGameObjectLoader(&gameObjectLoader);

    componentLoader.setGame(this);

    componentLoader.setTransformEngine(&transformEngine);
    componentLoader.setCollisionEngine(&collisionEngine);
    componentLoader.setPhysicsEngine(&physicsEngine);
    componentLoader.setEventEngine(&eventEngine);
    componentLoader.setLogicEngine(&logicEngine);
    componentLoader.setRenderEngine(&renderEngine);
    componentLoader.setRayCastingEngines(&rayCastingEngine);

    //end of component loader injections

    //component factory injections

    componentFactory.setComponentLoader(&componentLoader);
    componentFactory.setGameObjectLoader(&gameObjectLoader);

    componentFactory.setLogicEngine(&logicEngine);

    //end of component factory injections
    gameObjectFactory.setComponentFactory(&componentFactory);

    eventFactory.setGame(this);
    eventFactory.setEventEngine(&eventEngine);
    inputFactory.setInputEngine(&inputEngine);

    getCurrentLevel().objects.setComponentLoader(&componentLoader);

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
    dataFileParser.setGame(this);

    componentFactory.setGame(this);
    gameObjectFactory.setGame(this);
    eventFactory.setGame(this);
    inputFactory.setGame(this);
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
    input.setKeyInput("objectDebug",sf::Keyboard::F2);
    input.setKeyInput("debug",sf::Keyboard::F3);
    input.setKeyInput("transformDebug",sf::Keyboard::F4);
    input.setKeyInput("collisionDebug",sf::Keyboard::F5);
    input.setKeyInput("pathingDebug",sf::Keyboard::F6);
    input.setKeyInput("raycastingDebug",sf::Keyboard::F7);
    input.setKeyInput("runDebugScript",sf::Keyboard::F8);
    input.setKeyInput("eventDebug",sf::Keyboard::F9);

}

void Game::initialiseTests()
{
    debug->println("setting up tests");
    input.setKeyInput("changeScene",sf::Keyboard::F10);

    //for testing only
    transformEngine.setWrapAround(false);


}

void Game::initialisePlayers()
{
    ViewPort & viewPort = gameWindow->primaryView;
    inputFactory.detectControllers();
    debug->println("adding players");
    GameObject& player = getCurrentLevel().objects.objects["player_1"];
    rapidjson::Document config = resourceLoader.loadJsonFile("config/player.json");
    if(config.HasMember("player_start") && config["player_start"].IsObject())
    {
        sf::Vector2i playerStart;
        playerStart.x = config["player_start"].HasMember("x") && config["player_start"]["x"].IsNumber()
                ? config["player_start"]["x"].GetInt()
                : 0;

        playerStart.y = config["player_start"].HasMember("y") && config["player_start"]["y"].IsNumber()
                ? config["player_start"]["y"].GetInt()
                : 0;

        sf::Vector2f absPlayerStart = grid.getCentre(playerStart);

        componentLoader.getTransform(player.transform).setPosition(absPlayerStart);
    }

    viewPort.bounds = getCurrentLevel().cameraSettings.bounds.asSFFloatRect();
    viewPort.focusedTransform =  player.getTransform();
}

void Game::initialiseEnvironment()
{

    std::string rawJson = resourceLoader.loadFileAsString("config/entities.json");
    rapidjson::Document entityConfig;
    entityConfig.Parse(rawJson.c_str());
    assert(entityConfig["parentdirectory"].IsString());
    assert(entityConfig["entities"].IsArray());

    std::string eDir = entityConfig["parentdirectory"].GetString();
    const rapidjson::Value & entitiesJson = entityConfig["entities"];

    for (rapidjson::SizeType i = 0; i < entitiesJson.Size(); i++)
    {
        debug->println(eDir + "/" + entitiesJson[i].GetString());
        std::string entJsonString = resourceLoader.loadFileAsString(eDir + "/" + entitiesJson[i].GetString());
        rapidjson::Document entityJson;
        entityJson.Parse(entJsonString.c_str());
        std::string name = entityJson["name"].GetString();
        GameObjectPattern g;
        g.parseFromJson(entJsonString);
        entities[name] = g;
    }

    rapidjson::Document levelConfig = resourceLoader.loadJsonFile("config/levels.json");
    assert(levelConfig["parentdirectory"].IsString());
    assert(levelConfig["levels"].IsArray());

    std::string lDir = levelConfig["parentdirectory"].GetString();

    const rapidjson::Value & levelsJson = levelConfig["levels"];

    for (rapidjson::SizeType i = 0; i < levelsJson.Size(); i++)
    {
        debug->println("loading " + lDir + "/" + levelsJson[i].GetString());
        Level lvl;
        lvl.setGame(this);
        lvl.loadLevelFromFile(lDir + "/" + levelsJson[i].GetString());
        levels[lvl.name]=lvl;
    }

}

void Game::stabiliseFrameRate(float currentFrameDuration)
{
    sf::Time sleepTime = sf::seconds(targetFrameDuration - currentFrameDuration);
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

InputMap Game::getInput() const
{
    return input;
}

void Game::setInput(const InputMap &value)
{
    input = value;
}

void Game::setGameWindow(window_ptr window)
{
    gameWindow = window;

}

window_ptr Game::getGameWindow()
{
    return gameWindow;
}

void Game::changeLevel(std::string level)
{
    currentLevel = level;
    gameObjectLoader.setGameObjects(&getCurrentLevel().objects);
    ViewPort & viewPort = gameWindow->primaryView;
    GameObject & player = getCurrentLevel().objects.objects["player_1"];
    viewPort.focusedTransform = player.getTransform();
    viewPort.bounds = getCurrentLevel().cameraSettings.bounds.asSFFloatRect();

    transformEngine.wake();
    collisionEngine.wake();
    renderEngine.wake();

    viewPort.focus();
}

Level &Game::getCurrentLevel()
{
    return levels[currentLevel];
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

