#include "gameobjectpattern.h"

using namespace BQ;

GameObjectPattern::GameObjectPattern()
{

}

bool GameObjectPattern::parseFromJson(std::string rawJson)
{
    rapidjson::Document doc;
    doc.Parse(rawJson.c_str());

    rapidjson::Value & components = doc["components"];

    if(components.HasMember("spriterenderers"))
    {
        rapidjson::Value spriteRenderers = components["spriterenderers"].GetArray();
        for (rapidjson::SizeType i = 0; i < spriteRenderers.Size(); i++)
        {
            spriteRendererPatterns.push_back(parseSpriteRenderer(spriteRenderers[i]));
        }
    }

    if(components.HasMember("collidables"))
    {
        rapidjson::Value collidables = components["collidables"].GetArray();
        for (rapidjson::SizeType i = 0; i < collidables.Size(); i++)
        {
            CollidablePattern c = parseCollidable(collidables[i]);
            if(collidables[i].HasMember("polygon"))
            {
                for(rapidjson::SizeType p = 0; p<collidables[i]["polygon"].Size(); p++)
                {

                    rapidjson::Value point = collidables[i]["polygon"][p].GetObject();
                    c.polygon.push_back(sf::Vector2f(point["x"].GetFloat(),point["y"].GetFloat()));
                }
            }
            collidablePatterns.push_back(c);
        }
    }
    return true;
}

SpriteRendererPattern GameObjectPattern::parseSpriteRenderer(rapidjson::Value & json)
{

    SpriteRendererPattern sprite;

    if(!json.HasMember("sheet"))
    {
        return sprite;
    }
    sprite.sheet = json["sheet"].GetString();

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

    return sprite;
}

CollidablePattern GameObjectPattern::parseCollidable(rapidjson::Value & json)
{
    CollidablePattern collidable;

    collidable.immovable = json.HasMember("immovable") ? json["immovable"].GetBool() : false;

    return collidable;
}

