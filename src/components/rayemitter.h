#ifndef RAYEMITTER_H
#define RAYEMITTER_H

#include<component.h>

namespace BQ{
class RayEmitter : public Component
{
public:
    RayEmitter();

    std::vector<std::string> targets;
    std::vector<sf::Vector2f> positions;

    void addTarget(std::string);
    std::string getTarget(int);

    void update();
    void wake();

};
}
#endif // RAYEMITTER_H
