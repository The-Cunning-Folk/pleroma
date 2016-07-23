#include "tilelayer.h"

using namespace BQ;
TileLayer::TileLayer()
{
    defaultTile.index = -1;
    tileset = "";
}

bool TileLayer::parse(const rapidjson::Value & layerJson)
{
    if(layerJson.HasMember("sheet"))
    {
        tileset = layerJson["sheet"].GetString();
    }

    defaultTile.index = layerJson.HasMember("default")
            ? layerJson["default"].GetInt()
            : -1;

    return true;
}

Tile &TileLayer::getTile(sf::Vector2i p)
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

