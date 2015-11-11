#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>

namespace BQ{
class Logger
{
private:

    std::string label;
    std::ofstream logfile;
    bool suppressed;
    std::string filepath;


public:
    Logger (const Logger&);
    Logger& operator=(const Logger&);

    Logger(): logfile("log.log",std::ofstream::app) {}

    std::string getLabel() const;
    void setLabel(const std::string &value);

    void setLogfile(const std::string &value);

    void open();
    void close();

    bool getSuppressed() const;
    void setSuppressed(bool value);

    void println(std::string);
    void printVal(std::string, std::string);
    void printVal(std::string, float);
    void printVal(std::string, int);
    void printVal(std::string, long);
    void printVal(std::string, double);


    std::string getFilepath() const;
};
}

#endif // LOGGER_H
