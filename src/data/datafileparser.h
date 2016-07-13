#ifndef DATAFILEPARSER_H
#define DATAFILEPARSER_H

#include <gameobject.h>

namespace BQ{

class Game;

class DataFileParser
{
public:
    DataFileParser();

    Game * game;

    bool parseSpriteRenderer(rapidjson::Value &, SpriteRenderer &);
    bool parseCollidable(rapidjson::Value &, Collidable &);

    Game *getGame() const;
    void setGame(Game *value);
};

}
#endif // DATAFILEPARSER_H
