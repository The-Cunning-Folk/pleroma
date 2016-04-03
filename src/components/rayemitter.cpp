#include "rayemitter.h"

using namespace BQ;

RayEmitter::RayEmitter()
{
    typeId = "rayemitter";
}

void RayEmitter::addTarget(std::string t)
{
    targets.push_back(t);
}

std::string RayEmitter::getTarget(int index)
{
    if(index >= 0 && index < targets.size())
    {
        return targets[index];
    }
    else
    {
        return "null";
    }
}

void RayEmitter::update()
{

}

