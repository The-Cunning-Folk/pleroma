#include "transformengine.h"

using namespace BQ;

TransformEngine::TransformEngine()
{

}

void TransformEngine::run()
{
    for(unsigned int i=0; i<transforms.size(); i++)
    {
        //update all the transforms!
        transforms[i].update();
    }
}

void TransformEngine::drawDebug()
{
    for(unsigned int i=0; i<transforms.size(); i++)
    {
        //draw all the transforms!
        gameWindow->draw(transforms[i]);
    }
}

Transform *TransformEngine::addTransform()
{
    transforms.resize(transforms.size() + 1);
    if(debug != NULL){
        transforms.back().setDebug(debug);
    }
    transforms.back().index = transforms.size();
    return(&transforms.back());
}
