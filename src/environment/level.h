#ifndef LEVEL_H
#define LEVEL_H

#include<SFML/Graphics.hpp>
#include<rapidjson/document.h>
#include<tilemap.h>
#include<gameobjectstore.h>
#include<camerasettings.h>

namespace BQ
{
class Game;

class Level
{

public:
    Level();

    Game * game;

    std::string name;

    CameraSettings cameraSettings;

    GameObjectStore objects;

    TileMap groundMap;
    TileMap ceilingMap;

    bool loadLevelFromFile(std::string);

    Game *getGame() const;
    void setGame(Game *value);
};
}

#endif // LEVEL_H
