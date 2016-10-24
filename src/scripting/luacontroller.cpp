#include "luacontroller.h"

#include <game.h>

using namespace BQ;

LuaController::LuaController()
{
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::io);
    bindLuaFunctions();
    bindTypes();
    bindFunctions();
}

void LuaController::bindTypes()
{
    lua.new_usertype<GameObject>("Object",
                                 "name", &GameObject::name,
                                 "transform", &GameObject::transform,
                                 "components", &GameObject::components
                                 );
}

void LuaController::bindFunctions()
{
    lua.set_function("changeLevel", [&](std::string s) {
        game->changeLevel(s);
    });
    lua.set_function("getObject", [&](std::string s) {
        return game->getCurrentLevel().objects.objects[s];
    });
}

void LuaController::bindLuaFunctions()
{
    lua.script_file("var/global_scripts/global.lua");
}


Game *LuaController::getGame() const
{
    return game;
}

void LuaController::setGame(Game *value)
{
    game = value;
}

