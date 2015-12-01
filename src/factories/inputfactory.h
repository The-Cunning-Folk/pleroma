#ifndef INPUTFACTORY_H
#define INPUTFACTORY_H

#include<SFML/Graphics.hpp>

#include<factory.h>

#include<inputengine.h>


namespace BQ{
class InputFactory : public Factory
{
public:
    InputFactory();

    std::vector<int> controllers;

    InputEngine* inputEngine;

    void detectControllers();

    InputEngine *getInputEngine() const;
    void setInputEngine(InputEngine *value);
};
}

#endif // INPUTFACTORY_H
