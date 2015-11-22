#include "transformengine.h"

using namespace BQ;

TransformEngine::TransformEngine()
{

}

Transform *TransformEngine::addTransform()
{
    transforms.resize(transforms.size() + 1);
    return(&transforms.back());
}
