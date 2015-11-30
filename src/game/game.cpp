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
    float logicTime = debug->time.getSeconds("logicTime");
    inputEngine.run();
    transformEngine.run();

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

    initialisePlayers();

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
   componentFactory.setInputEngine(&inputEngine);

   gameObjectFactory.setStack(&gameObjects);
   gameObjectFactory.setDebug(debug);
   gameObjectFactory.setComponentFactory(&componentFactory);

   eventFactory.setEventEngine(&eventEngine);
   eventFactory.setDebug(debug);

   eventEngine.setGameWindow(gameWindow);
   inputEngine.setGameWindow(gameWindow);
   transformEngine.setGameWindow(gameWindow);

   inputEngine.setEventFactory(&eventFactory);

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

    for(int i = 0; i<8; i++)
    {
        bool connected = sf::Joystick::isConnected(i);
        if(connected)
        {
            debug->printinfo("joystick: " + std::to_string(i));
            unsigned int buttons = sf::Joystick::getButtonCount(i);
            debug->printinfo("buttons: " + std::to_string(buttons));
            bool hasX = sf::Joystick::hasAxis(i, sf::Joystick::X);
            bool hasY = sf::Joystick::hasAxis(i, sf::Joystick::Y);
            bool hasZ = sf::Joystick::hasAxis(i, sf::Joystick::Z);
            bool hasR = sf::Joystick::hasAxis(i, sf::Joystick::R);
            bool hasU = sf::Joystick::hasAxis(i, sf::Joystick::U);
            bool hasV = sf::Joystick::hasAxis(i, sf::Joystick::V);

            debug->printinfo("has X: " + std::to_string(hasX));
            debug->printinfo("has Y: " + std::to_string(hasY));
            debug->printinfo("has Z: " + std::to_string(hasZ));
            debug->printinfo("has R: " + std::to_string(hasR));
            debug->printinfo("has U: " + std::to_string(hasU));
            debug->printinfo("has V: " + std::to_string(hasV));

            std::vector<std::string> axes;

            if(hasX){axes.push_back("X");}
            if(hasY){axes.push_back("Y");}
            if(hasZ){axes.push_back("Z");}
            if(hasR){axes.push_back("R");}
            if(hasU){axes.push_back("U");}
            if(hasV){axes.push_back("V");}

            std::string axesList = "";

            for(int j=0; j<axes.size(); j++)
            {
                axesList += axes[j];
                if(j!=axes.size()-1)
                {
                    axesList += ", ";
                }
            }

            debug->printinfo("found a controller with " + std::to_string(buttons)
                             + " buttons, and " + axesList + " axes");


        }
    }
}

void Game::initialisePlayers()
{
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

