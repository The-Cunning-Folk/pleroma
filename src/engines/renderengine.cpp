#include "renderengine.h"

#include<game.h>

using namespace BQ;

RenderEngine::RenderEngine()
{

}


std::vector<SpriteRenderer> RenderEngine::getSprites() const
{
    return sprites;
}

void RenderEngine::setSprites(const std::vector<SpriteRenderer> &value)
{
    sprites = value;
}

BQ::SpriteRenderer &BQ::RenderEngine::addSpriteRenderer()
{
    sprites.resize(sprites.size()+1);
    sprites.back().index = sprites.size()-1;
    sprites.back().name = placeholder + std::to_string(sprites.size());
    return sprites.back();
}

SpriteRenderer &RenderEngine::getSpriteRenderer(int index)
{
    if(index >=0 && index < sprites.size())
    {
        return sprites[index];
    }
    else
    {
        debug->printerr("requested spriterenderer out of bounds");
        return sprites[0]; //todo: this could cause a segfault! Very bad >:(
    }
}

void RenderEngine::wake()
{
    //load sprite sheets

    //load and parse textures.json
    rapidjson::Document tconfig = resourceLoader->loadJsonFile("config/textures.json");

    //get the parent directory for the spritesheets
    assert(tconfig["parentdirectory"].IsString());
    std::string tDir = tconfig["parentdirectory"].GetString();

    //load the spritesheets array
    const rapidjson::Value & files = tconfig["spritesheets"];
    assert(files.IsArray());

    for (rapidjson::SizeType i = 0; i < files.Size(); i++)
    {
        debug->println(tDir + "/" + files[i].GetString());
        rapidjson::Document spritesheetJson = resourceLoader->loadJsonFile(tDir + "/" + files[i].GetString());

        assert(spritesheetJson["name"].IsString());
        assert(spritesheetJson["path"].IsString());
        std::string sheetName = spritesheetJson["name"].GetString();
        std::string sheetPath = spritesheetJson["path"].GetString();

        const rapidjson::Value & animationsJson = spritesheetJson["sprites"];

        assert(animationsJson.IsArray());

        //construct a spritesheet object here
        if ( spriteSheets.find(sheetName) != spriteSheets.end() ) {
            debug->printwarn("duplicate sprite sheet defined in config: " + sheetName);
          // not found
        }
        else
        {
            SpriteSheet s;
            s.texture = sheetPath;

            for (rapidjson::SizeType j=0 ; j<animationsJson.Size(); j++)
            {

                assert(animationsJson[j]["name"].IsString());
                std::string sprName = animationsJson[j]["name"].GetString();
                const rapidjson::Value & frames = animationsJson[j]["frames"];
                assert(frames.IsArray());
                std::vector<sf::IntRect> rects;
                for (rapidjson::SizeType k=0 ; k<frames.Size(); k++)
                {
                    sf::IntRect r;
                    r.left = frames[k]["l"].GetInt();
                    r.top = frames[k]["t"].GetInt();
                    r.width = frames[k]["w"].GetInt();
                    r.height = frames[k]["h"].GetInt();
                    rects.push_back(r);
                }
                s.addSprite(sprName,rects);
            }

            spriteSheets[sheetName] = s;
        }

    }



}

void BQ::RenderEngine::start()
{

}

void BQ::RenderEngine::run()
{

    for(int i=0; i<sprites.size(); i++)
    {
        SpriteRenderer & s = sprites[i];
        s.depth = componentLoader->getTransform(s.transform).position.y + s.depthOffset;
    }
}

void BQ::RenderEngine::finish()
{

}

void BQ::RenderEngine::drawDebug()
{
    std::vector<SpriteRenderer> renderList;

    for(int i=0; i<activeComponents.size(); i++)
    {
        renderList.push_back(sprites[activeComponents[i]]);
    }

    std::sort(renderList.begin(),renderList.end());

    std::vector<int> renderOrder;

    for(int i=0; i<renderList.size(); i++)
    {
        renderOrder.push_back(renderList[i].index);
    }

    for(int i=0; i<renderOrder.size(); i++)
    {
        SpriteRenderer & s = sprites[renderOrder[i]];
        sf::Sprite spr;
        if ( spriteSheets.find(s.spritesheet) == spriteSheets.end() ) {
            spr.setTexture(resourceLoader->getTexture(""));
        }
        else
        {
            SpriteSheet& sheet = spriteSheets[s.spritesheet];
            spr.setTexture(resourceLoader->getTexture(sheet.texture));
            std::string clip = "";

            if(sheet.spriteFrames.find(s.clip) != sheet.spriteFrames.end())
            {
                clip = s.clip;
            }
            else if(sheet.spriteFrames.size() > 0)
            {
                clip = sheet.spriteFrames.begin()->first;
            }

            if(clip != "")
            {
                bool spritefound = true;
                if(s.frame < 0 || s.frame >= sheet.spriteFrames[clip].size())
                {
                    if(sheet.spriteFrames[clip].size() > 0)
                    {
                        s.frame = 0;
                    }
                    else
                    {
                        spritefound = false;
                    }
                }

                if(spritefound)
                {
                    spr.setTextureRect(sheet.spriteFrames[clip][s.frame]);
                }
            }


        }

        sf::Vector2f pos = componentLoader->getTransform(s.transform).position;
        if(s.centreOrigin)
        {
            pos.x -= 0.5*spr.getLocalBounds().width;
            pos.y -= 0.5*spr.getLocalBounds().height;
        }
        spr.setPosition(maths->round(pos + s.offset));
        gameWindow->draw(spr);
    }
}
