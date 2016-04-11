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
        debug->printerr("requested rayemitter out of bounds");
        return sprites[0]; //todo: this could cause a segfault! Very bad >:(
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
    }
}

void BQ::RenderEngine::finish()
{

}

void BQ::RenderEngine::drawDebug()
{
    for(int i=0; i<sprites.size(); i++)
    {
        SpriteRenderer & s = sprites[i];
        sf::Sprite spr;
        spr.setTexture(resourceLoader->getTexture(s.texture));
        sf::Vector2f pos = componentLoader->getTransform(s.transform).position;
        if(s.centreOrigin)
        {
            pos.x -= 0.5*spr.getLocalBounds().width;
            pos.y -= 0.5*spr.getLocalBounds().height;
        }
        spr.setPosition(pos + s.offset);
        gameWindow->draw(spr);
    }
}
