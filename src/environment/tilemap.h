#ifndef TILEMAP_H
#define TILEMAP_H

#include<map>
#include<SFML/Graphics.hpp>
#include<tilelayer.h>

namespace  BQ {
class TileMap
{
public:
    TileMap();

    std::string tileset;
    Tile defaultTile;
    int layers;

    std::vector<TileLayer> tileLayers;

    bool parse(const rapidjson::Value &);

    Tile & getTile(int,sf::Vector2i);

};
}

#endif // TILEMAP_H
