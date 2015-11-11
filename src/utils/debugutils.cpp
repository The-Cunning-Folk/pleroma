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

void DebugUtils::printerr(std::string error)
{
    std::string output = "[ERROR] - " + error;
    println(output);
}

void DebugUtils::printwarn(std::string warn)
{
    std::string output = "[WARNING] - " + warn;
    println(output);
}

void DebugUtils::printVal(std::string name, std::string val)
{
    std::string outString = name + " : " + val;
    println(outString);
}

void DebugUtils::printVal(std::string name, float val)
{
    std::string asString = std::to_string(val);
    printVal(name,asString);
}

void DebugUtils::printVal(std::string name, int val)
{
    std::string asString = std::to_string(val);
    printVal(name,asString);
}

void DebugUtils::printVal(std::string name, long val)
{
    std::string asString = std::to_string(val);
    printVal(name,asString);
}

void DebugUtils::printVal(std::string name, double val)
{
    std::string asString = std::to_string(val);
    printVal(name,asString);
}

