#ifndef LEVEL_H
#define LEVEL_H

#include<SFML/Graphics.hpp>
#include<tilemap.h>

namespace BQ
{
class Level
{
public:
    Level();
    TileMap tileMap;
};
}

#endif // LEVEL_H
