#include "game.h"

using namespace BQ;

Game::Game()
{

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

void Game::stabiliseFrameRate(float currentFrameDuration)
{
    sf::Time sleepTime = sf::seconds(targetFrameDuration - currentFrameDuration);
    if(sleepTime.asSeconds() < 0){

        std::string targetString = std::to_string(targetFrameDuration);
        std::string currentString = std::to_string(currentFrameDuration);

        std::string warning = "frame duration exceeded target";
        debug.printwarn(warning);
        debug.printVal("target frame duration",targetFrameDuration);
        debug.printVal("recorded frame duration",currentFrameDuration);
    }
    sf::sleep(sleepTime);
}

void Game::run()
{

    if(gameWindow == NULL){
        debug.println("no game window defined, the application will now exit");
        return;
    }

    debug.time.addClock("frameTime");
    debug.time.addClock("logicTime");

    sf::CircleShape test;

    test.setRadius(10);
    test.setFillColor(sf::Color::Blue);

    while(gameWindow->isOpen()){



        //game loop goes here

        gameWindow->updateEvents();
        gameWindow->clear();

        //get time since last window.clear call



        //logictime is for calculating how long it's been since the engines were last updated
        float logicTime = debug.time.getSeconds("logicTime");

        //logic here

        test.setRadius(rand()%20);

        //end logic

        //restart the logic timer
        debug.time.restartClock("logicTime");

        //drawing here

        gameWindow->draw(test);

        //end drawing

        float frameTime = debug.time.getSeconds("frameTime");
        stabiliseFrameRate(frameTime);

        frameTime = debug.time.getSecondsAndRestart("frameTime");
        float fps = 1.0/frameTime;

        gameWindow->display();


    }
}
