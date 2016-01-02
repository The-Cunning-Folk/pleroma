#ifndef FACTORY_H
#define FACTORY_H

#include <debugutils.h>
#include <mathsutils.h>

#include<iostream>
#include<vector>
#include<functional>
#include<memory>
#include<map>

namespace BQ {

class Game;

class Factory
{
public:
    Factory();

    Game* game;

    DebugUtils* debug;

    MathsUtils* maths;

    void setDebug(DebugUtils *value);

    void setMaths(MathsUtils *value);
    Game *getGame() const;
    void setGame(Game *value);
};

}

#endif // FACTORY_H
