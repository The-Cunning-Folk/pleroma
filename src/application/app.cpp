#include "app.h"

App::App()
{

    debug.errorLog = loggers.getError();
    debug.warnLog = loggers.getWarn();
    debug.infoLog = loggers.getInfo();

    game.setDebug(&debug);

}

void App::run(){

    debug.println("building window");

    window_ptr gameWindow = windowManager.addWindow("game",480,270,"Dev Build");

    game.setFrameRate(500);

    game.setGameWindow(gameWindow);

    game.run();

}

