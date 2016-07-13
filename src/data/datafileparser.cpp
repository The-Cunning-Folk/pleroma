#include "datafileparser.h"

#include <game.h>

using namespace BQ;

DataFileParser::DataFileParser()
{

}

bool DataFileParser::parseCollidable(rapidjson::Value & json, Collidable & collidable)
{
    collidable.immovable = json.HasMember("immovable") ? json["immovable"].GetBool() : false;

    if(json.HasMember("polygon"))
    {
        for(rapidjson::SizeType p = 0; p<json["polygon"].Size(); p++)
        {
            rapidjson::Value point = json["polygon"][p].GetObject();
            collidable.polygon.addPoint(point["x"].GetFloat(),point["y"].GetFloat());
        }
    }

    return true;

}

Game *DataFileParser::getGame() const
{
    return game;
}

void DataFileParser::setGame(Game *value)
{
    game = value;
}

bool DataFileParser::parseSpriteRenderer(rapidjson::Value & json, SpriteRenderer & sprite)
{

    if(!json.HasMember("sheet"))
    {
        return false;
    }

    sprite.spritesheet = json["sheet"].GetString();

    if(json.HasMember("clip"))
    {
        sprite.clip = json["clip"].GetString();
    }
    if(json.HasMember("offset"))
    {
        rapidjson::Value offset = json["offset"].GetObject();
        sprite.offset.x = offset.HasMember("x") ? offset["x"].GetFloat() : 0;
        sprite.offset.y = offset.HasMember("y") ? offset["y"].GetFloat() : 0;
    }

    sprite.depthOffset = json.HasMember("depth_offset") ? json["depth_offset"].GetFloat() : 0;
}

