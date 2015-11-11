#ifndef APP_H
#define APP_H

#include<windowmanager.h>
#include<debugutils.h>
#include<game.h>
#include<loggerfactory.h>

class App
{
public:
    App();

    void run();

private:

    BQ::WindowManager windowManager;
    BQ::DebugUtils debug;
    BQ::Game game;
    BQ::LoggerFactory loggers;
};

#endif // APP_H
