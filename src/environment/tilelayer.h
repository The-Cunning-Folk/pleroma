#ifndef TILELAYER_H
#define TILELAYER_H

#include <tile.h>
#include <SFML/Graphics.hpp>

namespace BQ
{

class TileLayer
{
public:
    TileLayer();

    Tile defaultTile;

    std::string tileset;
    std::map<int,std::map<int,Tile>> tiles;

    Tile & getTile(sf::Vector2i);

};
}

#endif // TILELAYER_H
