#ifndef LUACONTROLLER_H
#define LUACONTROLLER_H

#include<sol.hpp>
#include<rapidjson/document.h>
#include<map>

namespace BQ{

class Game;

class LuaController : public sol::state
{
public:

    LuaController();

    Game* game;

    std::map<std::string,sol::load_result> behaviourScripts;

    void bindTypes();
    void bindFunctions();
    void bindLuaFunctions();
    void bindBehaviours();

    Game *getGame() const;
    void setGame(Game *value);
};

}

#endif // LUACONTROLLER_H
