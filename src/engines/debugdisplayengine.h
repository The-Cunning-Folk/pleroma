#ifndef DEBUGDISPLAYENGINE_H
#define DEBUGDISPLAYENGINE_H

#include<engine.h>

namespace BQ {

class DebugDisplayEngine : public Engine
{
public:
    DebugDisplayEngine();

    bool display;

    void start();
    void run();
    void finish();
    void drawDebug();

private:
};

}

#endif // DEBUGDISPLAYENGINE_H
