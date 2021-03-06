#include "luacontroller.h"

#include <game.h>
#include <map>
#include <string>

using namespace BQ;

LuaController::LuaController()
{
    lua.open_libraries(
                sol::lib::base,
                sol::lib::package,
                sol::lib::io,
                sol::lib::string,
                sol::lib::table
                );

    bindLuaFunctions();
    bindTypes();
    bindFunctions();
}

void LuaController::bindTypes()
{
    //SFML data structures
    lua.new_usertype<sf::Vector2f>("vector2f",
                                   "x",&sf::Vector2f::x,
                                   "y",&sf::Vector2f::y
                                   );
    lua.new_usertype<sf::Vector2i>("vector2i",
                                   "x",&sf::Vector2i::x,
                                   "y",&sf::Vector2i::y
                                   );
    lua.new_usertype<sf::FloatRect>("float_rect",
                                    "l",&sf::FloatRect::left,
                                    "t",&sf::FloatRect::top,
                                    "w",&sf::FloatRect::width,
                                    "h",&sf::FloatRect::height
                                    );
    lua.new_usertype<sf::IntRect>("int_rect",
                                  "l",&sf::IntRect::left,
                                  "t",&sf::IntRect::top,
                                  "w",&sf::IntRect::width,
                                  "h",&sf::IntRect::height
                                  );

    //basic plemora structures
    lua.new_usertype<ConvexPolygon>("polygon",
                                    "position",&ConvexPolygon::position,
                                    "points",&ConvexPolygon::points,
                                    "bbox",&ConvexPolygon::bBox,
                                    "center",&ConvexPolygon::centre
                                    );

    lua.new_usertype<Animation>("animation",
                                "running",&Animation::running,
                                "stopped",&Animation::stopped,
                                "spf",&Animation::spf,
                                "rate",&Animation::rate,
                                "frame",&Animation::frame,
                                "play",&Animation::play,
                                "pause",&Animation::pause,
                                "stop",&Animation::stop
                                );

    lua.new_usertype<InputMap>("inputmap",
                               "button_pressed",&InputMap::buttonPressed,
                               "button_toggled",&InputMap::buttonToggled,
                               "key_pressed",&InputMap::keyPressed,
                               "key_toggled",&InputMap::keyToggled,
                               "set_key_input",
                               sol::resolve<void(std::string,std::string)>(&InputMap::setKeyInput),
                               "get_keys_down",&InputMap::getKeysDown
                               );


    //object structures
    lua.new_usertype<GameObject>("gameobject",
                                 "name", sol::readonly(&GameObject::name),
                                 "transform", &GameObject::transform,
                                 "components", &GameObject::components,
                                 "active", &GameObject::active
                                 );

    //component structures
    lua.new_usertype<Component>("component",
                                "index",sol::readonly(&Component::index),
                                "name",&Component::name,
                                "parent",sol::readonly(&Component::parent),
                                "transform",&Component::transform,
                                "type",sol::readonly(&Component::typeId),
                                "id",sol::readonly(&Component::uniqueId),
                                "active", &Component::active
                                );

    lua.new_usertype<Transform>("transform",
                                "grid_position", sol::readonly(&Transform::gridPosition),
                                "position", &Transform::position,
                                "velocity", &Transform::velocity,
                                "last_frame",sol::readonly(&Transform::lastFrame),
                                "step",sol::readonly(&Transform::step),
                                "correction",sol::readonly(&Transform::correction),
                                "size",&Transform::size,
                                "children",&Transform::children,
                                "move", sol::resolve<void(float,float)>( &Transform::move),
                                sol::base_classes,sol::bases<Component>()
                                );
    
    lua.new_usertype<Collidable>("collidable",
                                 "solid", &Collidable::solid,
                                 "opaque", &Collidable::opaque,
                                 "pathable", &Collidable::pathable,
                                 "diminutive", &Collidable::diminutive,
                                 "immovable", &Collidable::immovable,
                                 "interacts_with_physics", &Collidable::interactsWithPhysics,
                                 "polygon",&Collidable::polygon,
                                 sol::base_classes,sol::bases<Component>()
                                 );

    lua.new_usertype<RigidBody>("rigidbody",
                                "momentum", &RigidBody::momentum,
                                "restitution",&RigidBody::restitution,
                                "friction",&RigidBody::friction,
                                "set_mass",&RigidBody::setMass,
                                "get_mass",&RigidBody::getMass,
                                "inv_mass",&RigidBody::getInvmass,
                                sol::base_classes,sol::bases<Component>()
                                );

    lua.new_usertype<SpriteRenderer>("spriterenderer",
                                     "animation",&SpriteRenderer::animation,
                                     "offset",&SpriteRenderer::offset,
                                     "depth_offset",&SpriteRenderer::depthOffset,
                                     "depth",&SpriteRenderer::depth,
                                     "texture",&SpriteRenderer::texture,
                                     "spritesheet",&SpriteRenderer::spritesheet,
                                     "clip",&SpriteRenderer::clip,
                                     "frame",&SpriteRenderer::frame,
                                     "texture_rect",&SpriteRenderer::textureRect,
                                     sol::base_classes,sol::bases<Component>()
                                     );

    lua.new_usertype<RayEmitter>("rayemitter",
                                 "targets",&RayEmitter::targets,
                                 "positions",&RayEmitter::positions,
                                 "add_target",&RayEmitter::addTarget,
                                 "get_target",&RayEmitter::getTarget,
                                 sol::base_classes,sol::bases<Component>()
                                 );

    lua.new_usertype<PlayerInput>("playerinput",
                                  "map",&PlayerInput::inputMap,
                                  sol::base_classes,sol::bases<Component>()
                                  );

    lua.new_usertype<Event>("event",
                            "triggered_by",&Event::triggeredBy,
                            "script",&Event::script
                            );


}

void LuaController::bindFunctions()
{
    //global game functions
    lua.set_function("change_level", [&](std::string s) {
        game->changeLevel(s);
    });

    lua.set_function("delta", [&]() {
        return game->delta;
    });

    lua.set_function("current_level",[&](){
        return game->currentLevel;
    });

    lua.set_function("get_global_input", [&]() {
        return &(game->input);
    });

    lua.set_function("get_global_events",[&](){
        return game->eventEngine.events;
    });

    //object access functions
    lua.set_function("get_object", [&](std::string s) {
        return &(game->getCurrentLevel().objects.objects[s]);
    });

    lua.set_function("remove_object", [&](std::string s) {
        return game->getCurrentLevel().objects.removeObject(s);
    });

    lua.set_function("deactivate_object", [&](std::string s) {
        return game->getCurrentLevel().objects.deactivateObject(s);
    });

    lua.set_function("activate_object", [&](std::string s) {
        return game->getCurrentLevel().objects.activateObject(s);
    });

    //object-based component access functions
    lua.set_function("get_obj_transform", [&](std::string s){
        return &(game->componentLoader.getTransform(game->getCurrentLevel().objects.objects[s].transform));
    });

    //direct component access functions

    lua.set_function("get_transform", [&](int n) {
        return &(game->componentLoader.getTransform(n));
    });

    lua.set_function("get_collidable", [&](int n) {
        return &(game->componentLoader.getCollidable(n));
    });

    lua.set_function("get_rigidbody", [&](int n) {
        return &(game->componentLoader.getRigidBody(n));
    });

    lua.set_function("get_spriterenderer", [&](int n) {
        return &(game->componentLoader.getSpriteRenderer(n));
    });

    lua.set_function("get_rayemitter", [&](int n) {
        return &(game->componentLoader.getRayEmitter(n));
    });


}

void LuaController::bindLuaFunctions()
{
    //runs the global lua file which contains global script definitions
    lua.script_file("var/global_scripts/global.lua");
    lua.script_file("var/global_scripts/base_behaviour.lua");
}


Game *LuaController::getGame() const
{
    return game;
}

void LuaController::setGame(Game *value)
{
    game = value;
}

