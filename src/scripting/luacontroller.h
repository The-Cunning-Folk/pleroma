#ifndef LUACONTROLLER_H
#define LUACONTROLLER_H

#include<sol.hpp>

namespace BQ{

class Game;

class LuaController
{
public:

    LuaController();


    sol::state lua;
    Game* game;

    void bindTypes();
    void bindFunctions();
    void bindLuaFunctions();

    Game *getGame() const;
    void setGame(Game *value);
};

}

#endif // LUACONTROLLER_H
