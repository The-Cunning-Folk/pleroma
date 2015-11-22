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
    }
}

Transform *TransformEngine::addTransform()
{
    transforms.resize(transforms.size() + 1);
    return(&transforms.back());
}
