#ifndef APP_H
#define APP_H

#include<windowmanager.h>
#include<debugutils.h>

class App
{
public:
    App();

    void run();

private:

    BQ::WindowManager windowManager;
    BQ::DebugUtils debug;


};

#endif // APP_H
