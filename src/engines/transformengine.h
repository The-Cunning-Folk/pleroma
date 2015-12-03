#ifndef TRANSFORMENGINE_H
#define TRANSFORMENGINE_H

#include <engine.h>
#include <transform.h>
#include <grid.h>

namespace BQ{

class TransformEngine : public Engine
{
public:
    TransformEngine();

    Grid* grid;

    void run();
    void drawDebug();

    std::vector<Transform> transforms;

    Transform* addTransform();

    Grid *getGrid() const;
    void setGrid(Grid *value);
};
}

#endif // TRANSFORMENGINE_H
