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

    while(gameWindow->isOpen()){
        //game loop goes here

        gameWindow->updateEvents();

        gameWindow->clear();

        gameWindow->display();
    }
}
