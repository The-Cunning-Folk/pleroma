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

        float frameTime = debug.time.getSecondsAndRestart("frameTime");
        float fps = 1.0/frameTime;
        debug.printVal("fps",fps);

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

        gameWindow->display();




    }
}
