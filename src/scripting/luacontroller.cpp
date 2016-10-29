#include "luacontroller.h"

#include <game.h>
#include <map>
#include <string>

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
    //SFML data structures
    lua.new_usertype<sf::Vector2f>("Vector2f",
                                   "x",&sf::Vector2f::x,
                                   "y",&sf::Vector2f::y
                                   );
    lua.new_usertype<sf::Vector2i>("Vector2i",
                                   "x",&sf::Vector2i::x,
                                   "y",&sf::Vector2i::y
                                   );
    lua.new_usertype<sf::FloatRect>("FloatRect",
                                   "l",&sf::FloatRect::left,
                                   "t",&sf::FloatRect::top,
                                   "w",&sf::FloatRect::width,
                                   "h",&sf::FloatRect::height
                                   );
    lua.new_usertype<sf::IntRect>("IntRect",
                                   "l",&sf::IntRect::left,
                                   "t",&sf::IntRect::top,
                                   "w",&sf::IntRect::width,
                                   "h",&sf::IntRect::height
                                   );

    //basic plemora structures
    lua.new_usertype<ConvexPolygon>("Polygon",
                                    "position",&ConvexPolygon::position,
                                    "points",&ConvexPolygon::points,
                                    "bBox",&ConvexPolygon::bBox,
                                    "center",&ConvexPolygon::centre
                                   );

    //object structures
    lua.new_usertype<GameObject>("Object",
                                 "name", &GameObject::name,
                                 "transform", &GameObject::transform,
                                 "components", &GameObject::components
                                 );

    //component structures
    lua.new_usertype<Collidable>("Collidable",
                                 "solid", &Collidable::solid,
                                 "opaque", &Collidable::opaque,
                                 "pathable", &Collidable::pathable,
                                 "diminutive", &Collidable::diminutive,
                                 "immovable", &Collidable::immovable,
                                 "interactsWithPhysics", &Collidable::interactsWithPhysics,
                                 "polygon",&Collidable::polygon,
                                 "parent",&Collidable::parent
                                 );
}

void LuaController::bindFunctions()
{
    //global game functions
    lua.set_function("change_level", [&](std::string s) {
        game->changeLevel(s);
    });

    //object access functions
    lua.set_function("get_object", [&](std::string s) {
        return &(game->getCurrentLevel().objects.objects[s]);
    });

    //object-based component access functions


    //direct component access functions
    lua.set_function("get_collidable", [&](int n) {
        return &(game->componentFactory.componentLoader->getCollidable(n));
    });

}

void LuaController::bindLuaFunctions()
{
    //runs the global lua file which contains global script definitions

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

