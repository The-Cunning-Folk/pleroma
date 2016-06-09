#ifndef RAYCASTINGENGINE_H
#define RAYCASTINGENGINE_H

#include <engine.h>
#include <simpleray.h>
#include <collidable.h>
#include <rayemitter.h>

namespace BQ {

class RaycastingEngine : public Engine
{
public:
    RaycastingEngine();

    std::vector<RayEmitter> rayEmitters;

    SimpleRay& createBasicRay(sf::Vector2f,sf::Vector2f);
    SimpleRay& createOwnedRay(sf::Vector2f,sf::Vector2f,GameObject&);
    SimpleRay& createOwnedRay(GameObject&,sf::Vector2f);
    SimpleRay& createTargettedRay(GameObject &, GameObject &);

    void wake();
    void start();
    void run();
    void finish();
    void drawDebug();

    std::vector<SimpleRay> getSimpleRays() const;
    void setSimpleRays(const std::vector<SimpleRay> &value);

    RayEmitter & addRayEmitter();
    RayEmitter & getRayEmitter(int);


protected:

    std::vector<SimpleRay> simpleRays;
};

}

#endif // RAYCASTINGENGINE_H
