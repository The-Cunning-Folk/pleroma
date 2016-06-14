#include "tilemap.h"

using namespace BQ;
TileMap::TileMap()
{

}

Tile &TileMap::getTile(sf::Vector2i p)
{
    if(tiles.find(p.x) != tiles.end() && tiles[p.x].find(p.y) != tiles[p.x].end())
    {
        return tiles[p.x][p.y];
    }
    else
    {
        return defaultTile;
    }
}

