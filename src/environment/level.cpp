#include "level.h"

#include <game.h>

using namespace BQ;

Level::Level()
{

}

bool Level::loadLevelFromFile(std::string path)
{
    GameObjectFactory & gameObjectFactory = game->gameObjectFactory;
    ComponentFactory & componentFactory = game->componentFactory;
    DebugUtils * debug = game->debug;

    rapidjson::Document levelJson = game->resourceLoader.loadJsonFile(path);

    assert(levelJson["name"].IsString());
    name = levelJson["name"].GetString();

    objects.level = name;

    //player
    GameObject & player = gameObjectFactory.newPlayerObject(objects);

    if(levelJson.HasMember("player"))
    {
        rapidjson::Value playerJson = levelJson["player"].GetObject();
        if(playerJson.HasMember("start"))
        {
            rapidjson::Value playerStartJson = playerJson["start"].GetObject();
            sf::Vector2i pos;

            pos.x = playerStartJson.HasMember("x") && playerStartJson["x"].IsNumber()
                        ? playerStartJson["x"].GetInt()
                        : 0;

            pos.y = playerStartJson.HasMember("y") && playerStartJson["y"].IsNumber()
                        ? playerStartJson["y"].GetInt()
                        : 0;

            Transform & pt = objects.transforms[player.transform];
            pt.setPosition(game->grid.getCentre(pos));

        }
    }

    //camera
    if(levelJson.HasMember("camera") && levelJson["camera"].IsObject())
    {
        rapidjson::Value cameraConfig = levelJson["camera"].GetObject();

        if(cameraConfig.HasMember("bounds"))
        {
            if (cameraConfig["bounds"].IsObject())
            {
                rapidjson::Value cameraBoundsConfig = cameraConfig["bounds"].GetObject();
                if(cameraBoundsConfig.HasMember("w") && cameraBoundsConfig.HasMember("h"))
                {
                    cameraSettings.bounds.height = cameraBoundsConfig["h"].GetFloat();
                    cameraSettings.bounds.width = cameraBoundsConfig["w"].GetFloat();
                    cameraSettings.bounds.left = cameraBoundsConfig.HasMember("l") && cameraBoundsConfig["l"].IsNumber()
                            ? cameraBoundsConfig["l"].GetFloat()
                            : 0;
                    cameraSettings.bounds.top = cameraBoundsConfig.HasMember("t") && cameraBoundsConfig["t"].IsNumber()
                            ? cameraBoundsConfig["t"].GetFloat()
                            : 0;
                }
            }
        }
    }

    //walls
    if(levelJson.HasMember("walls") && levelJson["walls"].IsArray())
    {
        for(rapidjson::SizeType w = 0; w<levelJson["walls"].Size(); w++)
        {
            rapidjson::Value wallJson = levelJson["walls"][w].GetObject();
            if (    wallJson.HasMember("l")
                    && wallJson.HasMember("t")
                    && wallJson.HasMember("h")
                    && wallJson.HasMember("w") )
            {

                float l = wallJson["l"].GetFloat();
                float t = wallJson["t"].GetFloat();
                float w = wallJson["w"].GetFloat();
                float h = wallJson["h"].GetFloat();

                std::vector<sf::Vector2f> points;

                float hw = 0.5*w;
                float hh = 0.5*h;
                points.push_back(sf::Vector2f(-hw,-hh));
                points.push_back(sf::Vector2f(hw,-hh));
                points.push_back(sf::Vector2f(hw,hh));
                points.push_back(sf::Vector2f(-hw,hh));

                GameObject & wall = gameObjectFactory.newObject(objects);
                Collidable & c = componentFactory.newCollidable(objects,points);
                c.immovable = true;
                wall.addComponent("hitbox",c);

                Transform & wt = objects.transforms[wall.transform];
                wt.setPosition(sf::Vector2f(l+hw,t+hh));

            }

        }
    }

    //entities
    if(levelJson.HasMember("entities"))
    {

        assert(levelJson["entities"].IsArray());

        for(rapidjson::SizeType e = 0; e<levelJson["entities"].Size(); e++)
        {
            rapidjson::Value ent = levelJson["entities"][e].GetObject();

            if(ent.HasMember("type"))
            {
                GameObject & entity = ent.HasMember("id")
                        ? gameObjectFactory.buildGameObjectFromPattern(objects,game->entities[ent["type"].GetString()],ent["id"].GetString())
                    : gameObjectFactory.buildGameObjectFromPattern(objects,game->entities[ent["type"].GetString()]);

                int xPos = ent["x"].GetInt();
                int yPos = ent["y"].GetInt();

                objects.transforms[entity.transform].setPosition(game->grid.getCentre(xPos,yPos));

            }

        }
    }

    //ground sheet
    if(levelJson.HasMember("ground") && levelJson["ground"].IsObject())
    {
        assert(levelJson["ground"].IsObject());
        rapidjson::Value ground = levelJson["ground"].GetObject();

        if(!groundMap.parse(ground))
        {
            debug->println("load error in ground object");
        }
        else
        {
            for(rapidjson::SizeType lnum = 0; lnum<groundMap.tileLayers.size(); lnum++)
            {
                int reverse = groundMap.tileLayers.size() - 1 - lnum;
                TileLayer & layer = groundMap.tileLayers[lnum];
                rapidjson::Value layerJson = ground["layers"][reverse].GetObject();

                if(layerJson.IsNull())
                {
                    continue;
                }

                if(!layer.parse(layerJson))
                {
                    debug->println("load error in ground layer " + std::to_string(lnum));
                    continue;
                }

                if(layer.tileset=="")
                {
                    layer.tileset = ground["default_sheet"].GetString();
                }

                if(lnum == 0 && layer.defaultTile.index == -1)
                {
                    layer.defaultTile.index = groundMap.defaultTile.index;
                }

                if(layerJson.HasMember("tiles") && layerJson["tiles"].IsArray())
                {
                    assert(layerJson["tiles"].IsArray());

                    for(rapidjson::SizeType j=0; j<layerJson["tiles"].Size();j++)
                    {
                        if(!layerJson["tiles"][j].IsObject())
                        {
                            game->debug->println("tile " + std::to_string(j) + " in layer " + std::to_string(lnum) + " has a syntax error");
                            continue;
                        }
                        rapidjson::Value tileJson = layerJson["tiles"][j].GetObject();
                        Tile tile;
                        if(tile.parse(tileJson))
                        {
                            layer.tiles[tile.x][tile.y] = tile;
                        }
                        else
                        {
                            debug->println("error in ground tile " + std::to_string(j) + " in layer " + std::to_string(lnum));
                        }
                    }
                }
            }
        }
    }

    //ceiling
    if(levelJson.HasMember("ceiling"))
    {

        assert(levelJson["ceiling"].IsObject());
        rapidjson::Value ceiling = levelJson["ceiling"].GetObject();

        if(!ceilingMap.parse(ceiling))
        {
            debug->println("load error in ceiling object");
        }
        else
        {

            for(rapidjson::SizeType lnum = 0; lnum<ceilingMap.tileLayers.size(); lnum++)
            {
                int reverse = ceilingMap.tileLayers.size() - 1 - lnum;
                TileLayer & layer = ceilingMap.tileLayers[lnum];
                rapidjson::Value layerJson = ceiling["layers"][reverse].GetObject();

                if(layerJson.IsNull())
                {
                    continue;
                }

                if(!layer.parse(layerJson))
                {
                    debug->println("load error in ceiling layer " + std::to_string(lnum));
                    continue;
                }


                if(layer.tileset=="")
                {
                    layer.tileset = ceiling["default_sheet"].GetString();
                }

                if(layerJson.HasMember("tiles") && layerJson["tiles"].IsArray())
                {
                    for(rapidjson::SizeType j=0; j<layerJson["tiles"].Size();j++)
                    {
                        if(!layerJson["tiles"][j].IsObject())
                        {
                            game->debug->println("tile " + std::to_string(j) + " in layer " + std::to_string(lnum) + " has a syntax error");
                            continue;
                        }
                        rapidjson::Value tileJson = layerJson["tiles"][j].GetObject();
                        Tile tile;
                        if(tile.parse(tileJson))
                        {
                            layer.tiles[tile.x][tile.y] = tile;
                        }
                        else
                        {
                            debug->println("error in ceiling tile " + std::to_string(j) + " in layer " + std::to_string(lnum));
                        }
                    }
                }
            }
        }
    }


    return true;
}

void Level::start()
{
    for(int i=0; i<objects.gamelogics.size();i++)
    {
        GameLogic & g = objects.gamelogics[i];
        for(int j=0; j<g.scripts.size(); j++)
        {
            ScriptBehaviour & s = g.scripts[j];
            if(s.instance != "")
            {
                sol::table self = game->luaCtrl[s.instance];
                if(self.valid() && game->luaCtrl[s.instance]["start"].valid())
                {
                    game->luaCtrl[s.instance]["start"](self,objects.objects[g.parent]);
                }
            }
        }
    }
}

Game *Level::getGame() const
{
    return game;
}

void Level::setGame(Game *value)
{
    game = value;
}


