#ifndef COLLIDABLEPATTERN_H
#define COLLIDABLEPATTERN_H

#include <factorypattern.h>

namespace BQ
{

class CollidablePattern : public FactoryPattern
{
public:
    CollidablePattern();

    bool immovable;
    bool solid;
    bool physical;
    bool diminutive;
    bool pathable;
    bool opaque;

    std::vector<sf::Vector2f> polygon;
};

}

#endif // COLLIDABLEPATTERN_H
