#include "loggerfactory.h"

using namespace BQ;

LoggerFactory::LoggerFactory()
{
    info.setLogfile("info.log");
    info.setLabel("[INFO]");

    warn.setLogfile("warn.log");
    warn.setLabel("[WARN]");

    error.setLogfile("error.log");
    error.setLabel("[ERROR]");
}

Logger* LoggerFactory::getError()
{
    return &error;
}



Logger* LoggerFactory::getWarn()
{
    return &warn;
}


Logger* LoggerFactory::getInfo()
{
    return &info;
}


