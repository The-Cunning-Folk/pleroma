#include "tile.h"

using namespace BQ;

Tile::Tile()
{

}

bool Tile::parse(const rapidjson::Value & tileJson)
{

    if(!(tileJson.HasMember("tile") && tileJson["tile"].IsInt()))
    {
        return false;
    }

    if(!(tileJson.HasMember("x") && tileJson["x"].IsInt()))
    {
        return false;
    }

    if(!(tileJson.HasMember("y") && tileJson["y"].IsInt()))
    {
        return false;
    }

    int sheetIndex = tileJson["tile"].GetInt();
    int xpos = tileJson["x"].GetInt();
    int ypos = tileJson["y"].GetInt();

    int rot = tileJson.HasMember("rot") && tileJson["rot"].IsInt()
            ? tileJson["rot"].GetInt()
            : 0;

    bool flipX = tileJson.HasMember("flipX") && tileJson["flipX"].IsBool()
            ? tileJson["flipX"].GetBool()
            : false;

    this->index = sheetIndex;
    this->x = xpos;
    this->y = ypos;
    this->rot = rot;
    this->flipX = flipX;
    return true;
}

