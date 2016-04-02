#ifndef RAYEMITTER_H
#define RAYEMITTER_H

#include<component.h>

namespace BQ{
class RayEmitter : public Component
{
public:
    RayEmitter();

    std::vector<std::string> targets;

    void addTarget(std::string);

    void update();

};
}
#endif // RAYEMITTER_H
