#include "logger.h"

using namespace BQ;


std::string Logger::getFilepath() const
{
    return filepath;
}
std::string Logger::getLabel() const
{
    return label;
}

void Logger::setLabel(const std::string &value)
{
    label = value;
}


void Logger::setLogfile(const std::string &value)
{
    close();
    filepath = value;
    open();
}

void Logger::open()
{
    logfile.open(filepath);
}

void Logger::close()
{
    logfile.close();
}

bool Logger::getSuppressed() const
{
    return suppressed;
}

void Logger::setSuppressed(bool value)
{
    suppressed = value;
}

void Logger::println(std::string output)
{
   logfile << label << " --- " << output << std::endl;
}

void Logger::printVal(std::string name, std::string val)
{
    std::string outString = name + " : " + val;
    println(outString);
}

void Logger::printVal(std::string name, float val)
{
    std::string asString = std::to_string(val);
    printVal(name,asString);
}

void Logger::printVal(std::string name, int val)
{
    std::string asString = std::to_string(val);
    printVal(name,asString);
}

void Logger::printVal(std::string name, long val)
{
    std::string asString = std::to_string(val);
    printVal(name,asString);
}

void Logger::printVal(std::string name, double val)
{
    std::string asString = std::to_string(val);
    printVal(name,asString);
}
