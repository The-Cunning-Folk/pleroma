#include "level.h"

#include <game.h>

using namespace BQ;

Level::Level()
{

}

bool Level::loadLevelFromFile(std::string path)
{
    GameObjectFactory & gameObjectFactory = game->gameObjectFactory;
    DebugUtils * debug = game->debug;

    rapidjson::Document levelJson = game->resourceLoader.loadJsonFile(path);

    assert(levelJson["name"].IsString());
    name = levelJson["name"].GetString();

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
                        ? gameObjectFactory.buildGameObjectFromPattern(game->entities[ent["type"].GetString()],ent["id"].GetString())
                    : gameObjectFactory.buildGameObjectFromPattern(game->entities[ent["type"].GetString()]);

                int xPos = ent["x"].GetInt();
                int yPos = ent["y"].GetInt();

                entity.loadTransform().setPosition(game->grid.getCentre(xPos,yPos));
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
                TileLayer & layer = groundMap.tileLayers[lnum];
                rapidjson::Value layerJson = ground["layers"][lnum].GetObject();

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

                if(layerJson.HasMember("map") && layerJson["map"].IsArray())
                {
                    assert(layerJson["map"].IsArray());

                    for(rapidjson::SizeType j=0; j<layerJson["map"].Size();j++)
                    {
                        if(!layerJson["map"][j].IsObject())
                        {
                            game->debug->println("tile " + std::to_string(j) + " in layer " + std::to_string(lnum) + " has a syntax error");
                            continue;
                        }
                        rapidjson::Value tileJson = layerJson["map"][j].GetObject();
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
                TileLayer & layer = ceilingMap.tileLayers[lnum];
                rapidjson::Value layerJson = ceiling["layers"][lnum].GetObject();

                if(!layer.parse(layerJson))
                {
                    debug->println("load error in ceiling layer " + std::to_string(lnum));
                    continue;
                }


                if(layer.tileset=="")
                {
                    layer.tileset = ceiling["default_sheet"].GetString();
                }

                if(layerJson.HasMember("map") && layerJson["map"].IsArray())
                {
                    for(rapidjson::SizeType j=0; j<layerJson["map"].Size();j++)
                    {
                        if(!layerJson["map"][j].IsObject())
                        {
                            game->debug->println("tile " + std::to_string(j) + " in layer " + std::to_string(lnum) + " has a syntax error");
                            continue;
                        }
                        rapidjson::Value tileJson = layerJson["map"][j].GetObject();
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
    //finish groundsheet
    return true;
}

Game *Level::getGame() const
{
    return game;
}

void Level::setGame(Game *value)
{
    game = value;
}


