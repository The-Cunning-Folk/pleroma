#include "app.h"

App::App()
{

}

void App::run(){

    debug.println("building window");

    window_ptr gameWindow = windowManager.addWindow("game",480,270,"Dev Build");

    game.setGameWindow(gameWindow);

    game.run();

}

