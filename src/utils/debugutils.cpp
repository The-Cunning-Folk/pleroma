#include "debugutils.h"

using namespace BQ;

DebugUtils::DebugUtils()
{
    time.injectDebug(this);
}

void DebugUtils::println(std::string output)
{
   std::cout << output << std::endl;
}

