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

    bool parseSpriteRenderer(rapidjson::Value &);
    bool parseCollidable(rapidjson::Value &);

    std::string typeName;

    std::vector<SpriteRendererPattern> spriteRendererPatterns;
    std::vector<CollidablePattern> collidablePatterns;

};
}

#endif // GAMEOBJECTPATTERN_H
