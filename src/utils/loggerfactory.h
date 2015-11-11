#ifndef LOGGERFACTORY_H
#define LOGGERFACTORY_H

#include<logger.h>

namespace BQ {
class LoggerFactory
{
public:
    LoggerFactory();

    Logger info;
    Logger warn;
    Logger error;

    Logger* getInfo();
    Logger* getWarn();
    Logger* getError();
};
}

#endif // LOGGERFACTORY_H
