#include "tilemap.h"

using namespace BQ;
TileMap::TileMap()
{
    layers = 0;
    tileLayers.resize(0);
}

bool TileMap::parse(const rapidjson::Value & json)
{
    defaultTile.index = json.HasMember("default_tile") && json["default_tile"].IsInt()
            ? json["default_tile"].GetInt()
            : -1;

    this->tileset = json.HasMember("default_sheet") && json["default_sheet"].IsString()
            ? json["default_sheet"].GetString()
            : "";

    layers = json.HasMember("layers") && json["layers"].IsArray()
            ? json["layers"].GetArray().Size()
            : 0;

    tileLayers.resize(layers);

    return true;
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

