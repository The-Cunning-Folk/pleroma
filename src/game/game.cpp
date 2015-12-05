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

    //for testing only
    transformEngine.setWrapAround(true);
    transformEngine.setBounds(sf::IntRect(0,0,ceil(gameWindow->getWidth()/grid.getScale()),ceil(gameWindow->getHeight()/grid.getScale())));
    //remove later!
}

void Game::runEngines()
{

    inputEngine.run();
    transformEngine.run();
    collisionEngine.run();

    float logicTime = debug->time.getSeconds("logicTime");
    eventEngine.setDelta(logicTime);
    eventEngine.run();
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

    debug->println("starting game loop");

    //end temporary behaviours

    while(gameWindow->isOpen()){
        //game loop goes here

        gameWindow->updateEvents();
        gameWindow->clear();

        //get time since last window.clear call
        //logictime is for calculating how long it's been since the engines were last updated


        //logic here

        input.update();

        if(input.keyToggled("debug"))
            debug->println("display debug");

        //temporary behaviours

        runTests();

        runEngines();

        //end logic

        //restart the logic timer
        debug->time.restartClock("logicTime");

        //drawing here

        transformEngine.drawDebug();
        collisionEngine.drawDebug();


        //end drawing

        gameWindow->display();

        //framerate stuff
        float frameTime = debug->time.getSeconds("frameTime");
        stabiliseFrameRate(frameTime);
        frameTime = debug->time.getSecondsAndRestart("frameTime");
        float fps = 1.0/frameTime;
        //end framerate stuff

    }
}

void Game::initialiseInjections()
{
   debug->println("injecting dependencies");

   componentFactory.setDebug(debug);
   componentFactory.setTransformEngine(&transformEngine);
   componentFactory.setInputEngine(&inputEngine);
   componentFactory.setEventEngine(&eventEngine);
   componentFactory.setCollisionEngine(&collisionEngine);

   gameObjectFactory.setStack(&gameObjects);
   gameObjectFactory.setDebug(debug);
   gameObjectFactory.setComponentFactory(&componentFactory);

   eventFactory.setEventEngine(&eventEngine);
   eventFactory.setDebug(debug);

   inputFactory.setInputEngine(&inputEngine);
   inputFactory.setDebug(debug);

   eventEngine.setGameWindow(gameWindow);
   inputEngine.setGameWindow(gameWindow);
   transformEngine.setGameWindow(gameWindow);
   collisionEngine.setGameWindow(gameWindow);

   eventEngine.setDebug(debug);
   inputEngine.setDebug(debug);
   transformEngine.setDebug(debug);
   collisionEngine.setDebug(debug);

   transformEngine.setGrid(&grid);

   inputEngine.setEventFactory(&eventFactory);
   collisionEngine.setEventFactory(&eventFactory);

   grid.setDebug(debug);
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

}

void Game::initialiseTests()
{
    debug->println("setting up tests");
    input.setKeyInput("addObject",sf::Keyboard::F8);

    for(int i=0; i<10; i++)
    {
        GameObject* coll = gameObjectFactory.newCollisionObject();
        coll->setPosition(sf::Vector2f(i*16 + 16,120));
    }
}

void Game::initialisePlayers()
{
    inputFactory.detectControllers();
    debug->println("adding players");
    gameObjectFactory.newPlayerObject();

}

void Game::stabiliseFrameRate(float currentFrameDuration)
{
    sf::Time sleepTime = sf::seconds(targetFrameDuration - currentFrameDuration);
    if(sleepTime.asSeconds() < 0){

        std::string targetString = std::to_string(targetFrameDuration);
        std::string currentString = std::to_string(currentFrameDuration);

        std::string warning = "frame duration exceeded target";
        debug->printwarn(warning);
    }
    sf::sleep(sleepTime);
}

void Game::setDebug(DebugUtils *value)
{
    debug = value;
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

