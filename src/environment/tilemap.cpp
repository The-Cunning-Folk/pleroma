#include "tilemap.h"

using namespace BQ;
TileMap::TileMap()
{

}

Tile &TileMap::getTile(int layer, sf::Vector2i p)
{
    if(layer < tileLayers.size() && layer >= 0)
    {
        return tileLayers[layer].getTile(p);
    }
    else
    {
        return defaultTile;
    }
}

