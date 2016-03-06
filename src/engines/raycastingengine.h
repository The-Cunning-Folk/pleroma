#ifndef RAYCASTINGENGINE_H
#define RAYCASTINGENGINE_H

#include <engine.h>

namespace BQ {

class RaycastingEngine : public Engine
{
public:
    RaycastingEngine();



    void start();
    void run();
    void finish();
    void drawDebug();
};

}

#endif // RAYCASTINGENGINE_H
