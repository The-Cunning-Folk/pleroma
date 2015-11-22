#include "game.h"

using namespace BQ;

Game::Game()
{

}

void Game::runTests()
{
    //add temporary stuff here for testing and debugging so the loop doesn't get too cluttered
    if(input.keyToggled("addObject"))
        gameObjectFactory.newObject();
}

void Game::runEngines()
{
    transformEngine.run();
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

    sf::CircleShape test;
    test.setRadius(10);
    test.setFillColor(sf::Color::Blue);

    //end temporary behaviours

    while(gameWindow->isOpen()){
        //game loop goes here

        gameWindow->updateEvents();
        gameWindow->clear();

        //get time since last window.clear call
        //logictime is for calculating how long it's been since the engines were last updated
        float logicTime = debug->time.getSeconds("logicTime");

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

   componentFactory.setDebug(debug);
   componentFactory.setTransformEngine(&transformEngine);

   gameObjectFactory.setStack(&gameObjects);
   gameObjectFactory.setDebug(debug);
   gameObjectFactory.setComponentFactory(&componentFactory);

   transformEngine.setGameWindow(gameWindow);

   grid.setDebug(debug);
}

void Game::initialiseClocks()
{
    debug->time.addClock("frameTime");
    debug->time.addClock("logicTime");
}

void Game::initialiseInput()
{
    input.setKeyInput("menu",sf::Keyboard::Escape);
    input.setKeyInput("debug",sf::Keyboard::F3);

}

void Game::initialiseTests()
{
    input.setKeyInput("addObject",sf::Keyboard::F8);
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

