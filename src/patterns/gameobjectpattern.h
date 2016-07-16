#ifndef GAMEOBJECTPATTERN_H
#define GAMEOBJECTPATTERN_H

#include <vector>
#include <rapidjson/document.h>
#include <spriterendererpattern.h>
#include <collidablepattern.h>

namespace BQ
{

class GameObjectPattern
{
public:
    GameObjectPattern();

    bool parseFromJson(std::string);

    SpriteRendererPattern parseSpriteRenderer(rapidjson::Value &);
    CollidablePattern parseCollidable(rapidjson::Value &);

    std::vector<sf::Vector2f> parsePolygon(rapidjson::Value &);

    std::string typeName;

    std::vector<SpriteRendererPattern> spriteRendererPatterns;
    std::vector<CollidablePattern> collidablePatterns;

};
}

#endif // GAMEOBJECTPATTERN_H
