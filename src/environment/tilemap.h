#ifndef TILEMAP_H
#define TILEMAP_H

#include<map>
#include<SFML/Graphics.hpp>
#include<tile.h>

namespace  BQ {
class TileMap
{
public:
    TileMap();

    std::string tileset;
    Tile defaultTile;
    std::map<int,std::map<int,Tile>> tiles;

    Tile & getTile(sf::Vector2i);

};
}

#endif // TILEMAP_H
