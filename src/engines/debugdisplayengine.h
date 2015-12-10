#ifndef DEBUGDISPLAYENGINE_H
#define DEBUGDISPLAYENGINE_H

#include<engine.h>

namespace BQ {

class DebugDisplayEngine : public Engine
{
public:
    DebugDisplayEngine();

    bool display;

    void run();
    void drawDebug();

private:
};

}

#endif // DEBUGDISPLAYENGINE_H
