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

    inputEngine.run();
    transformEngine.setDelta(debug->time.getSeconds("logicTime"));
    transformEngine.run();


    //float logicTime = debug->time.getSeconds("logicTime");
    //eventEngine.setDelta(logicTime);
    eventEngine.run();

    collisionEngine.run();
    debugDisplayEngine.run();
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


    //end temporary behaviours

    while(window.isOpen()){
        //game loop goes here

        window.updateEvents();

        //get time since last window.clear call
        //logictime is for calculating how long it's been since the engines were last updated

        //logic here

        input.update();

        if(input.keyToggled("debug"))
            print.println("display debug");

        //temporary behaviours

        runTests();

        runEngines();

        //end logic

        //restart the logic timer
        print.time.restartClock("logicTime");

        window.clear();

        //drawing here

        transformEngine.drawDebug();
        collisionEngine.drawDebug();
        debugDisplayEngine.drawDebug();


        //end drawing

        window.display();

        //framerate stuff
        float frameTime = print.time.getSeconds("frameTime");
        stabiliseFrameRate(frameTime);
        frameTime = print.time.getSecondsAndRestart("frameTime");
        float fps = 1.0/frameTime;
        //print.printVal("fps",fps);
        //end framerate stuff

    }
}

void Game::initialiseInjections()
{
   debug->println("injecting dependencies");

   componentLoader.setTransformEngine(&transformEngine);
   componentFactory.setCollisionEngine(&collisionEngine);

   componentFactory.setDebug(debug);
   componentFactory.setTransformEngine(&transformEngine);
   componentFactory.setInputEngine(&inputEngine);
   componentFactory.setEventEngine(&eventEngine);
   componentFactory.setCollisionEngine(&collisionEngine);
   componentFactory.setComponentLoader(&componentLoader);
   componentFactory.setMaths(&math);

   gameObjectFactory.setStack(&gameObjects);
   gameObjectFactory.setDebug(debug);
   gameObjectFactory.setComponentFactory(&componentFactory);
   gameObjectFactory.setMaths(&math);

   eventFactory.setEventEngine(&eventEngine);
   eventFactory.setDebug(debug);

   inputFactory.setInputEngine(&inputEngine);
   inputFactory.setDebug(debug);

   eventEngine.setGame(this);
   inputEngine.setGame(this);
   transformEngine.setGame(this);
   collisionEngine.setGame(this);
   debugDisplayEngine.setGame(this);

   eventEngine.setGameWindow(gameWindow);
   inputEngine.setGameWindow(gameWindow);
   transformEngine.setGameWindow(gameWindow);
   collisionEngine.setGameWindow(gameWindow);
   debugDisplayEngine.setGameWindow(gameWindow);

   eventEngine.setDebug(debug);
   inputEngine.setDebug(debug);
   transformEngine.setDebug(debug);
   collisionEngine.setDebug(debug);
   debugDisplayEngine.setDebug(debug);

   collisionEngine.setMaths(&math);

   eventEngine.setComponentLoader(&componentLoader);
   collisionEngine.setComponentLoader(&componentLoader);

   transformEngine.setGrid(&grid);

   gameObjects.setComponentLoader(&componentLoader);

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

    //for testing only
    transformEngine.setWrapAround(true);
    debug->println(std::to_string(gameWindow->getWidth()));
    transformEngine.setBounds(sf::IntRect(0,0,ceil(gameWindow->getWidth()/grid.getScale()),ceil(gameWindow->getHeight()/grid.getScale())));
    //remove later!

    for(int i=1; i<6; i++)
    {
        for(int j=1; j<6; j++)
        {
            GameObject* coll = gameObjectFactory.newCollisionObject();
            coll->loadTransform().setPosition(sf::Vector2f(i*2*16 + 16,j*2*16+16));
        }
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
        //debug->printwarn(warning);
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

