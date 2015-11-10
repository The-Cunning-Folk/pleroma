#include "app.h"

App::App()
{

}

void App::run(){

    debug.println("building window");

    windowManager.addWindow("game",480,270,"Dev Build");

    windowManager.run();

}

