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

void DebugUtils::printerr(std::string output)
{
    if(errorLog!=NULL){
        errorLog->println(output);
    }
}

void DebugUtils::printwarn(std::string output)
{
    if(warnLog!= NULL){
        warnLog->println(output);
    }
}

void DebugUtils::printinfo(std::string output)
{
    if(infoLog!= NULL){
        infoLog->println(output);
    }
}

void DebugUtils::printVal(float val)
{
    std::string outString = std::to_string(val);
    println(outString);
}

void DebugUtils::printVal(int val)
{
    std::string outString = std::to_string(val);
    println(outString);
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

void DebugUtils::printVal(sf::FloatRect r)
{
    println(" l: " + std::to_string(r.left) + ", t: " + std::to_string(r.top) + ", w: " + std::to_string(r.width) + ", h: " + std::to_string(r.height));
}

void DebugUtils::printVal(sf::IntRect r)
{
    println(" l: " + std::to_string(r.left) + ", t: " + std::to_string(r.top) + ", w: " + std::to_string(r.width) + ", h: " + std::to_string(r.height));
}

void DebugUtils::printVal(sf::Vector2f v)
{
    println(" x: " + std::to_string(v.x) + ", y: " + std::to_string(v.y));
}

void DebugUtils::printVal(sf::Vector2i v)
{
    println(" x: " + std::to_string(v.x) + ", y: " + std::to_string(v.y));
}

void DebugUtils::printVal(bool b)
{
    b==true ? println("true") : println("false");
}

std::string DebugUtils::formatVector(sf::Vector2f v, int dec_places)
{
    std::stringstream streamX;
    streamX << std::fixed << std::setprecision(dec_places) << v.x;
    std::stringstream streamY;
    streamY << std::fixed << std::setprecision(dec_places) << v.y;

    std::string xPrec = streamX.str();
    std::string yPrec = streamY.str();

    return "(" + xPrec + " , " + yPrec + ")";
}
