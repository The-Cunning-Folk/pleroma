#ifndef COLLIDABLEPATTERN_H
#define COLLIDABLEPATTERN_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace BQ
{

class CollidablePattern
{
public:
    CollidablePattern();

    std::string name;
    bool immovable;
    std::vector<sf::Vector2f> polygon;
};

}

#endif // COLLIDABLEPATTERN_H
