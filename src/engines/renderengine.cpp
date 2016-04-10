#include "renderengine.h"

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

void BQ::RenderEngine::start()
{

}

void BQ::RenderEngine::run()
{

}

void BQ::RenderEngine::finish()
{

}

void BQ::RenderEngine::drawDebug()
{

}
