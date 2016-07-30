#ifndef RAYEMITTERPATTERN_H
#define RAYEMITTERPATTERN_H

#include <factorypattern.h>

namespace BQ {

class RayEmitterPattern : public FactoryPattern
{
public:
    RayEmitterPattern();

    std::vector<std::string> targets;
    std::vector<sf::Vector2f> positions;

};

}

#endif // RAYEMITTERPATTERN_H
