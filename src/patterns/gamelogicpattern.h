#ifndef GAMELOGICPATTERN_H
#define GAMELOGICPATTERN_H

#include <factorypattern.h>
#include <scriptbehaviour.h>

namespace BQ
{

class GameLogicPattern : public FactoryPattern
{
public:
    GameLogicPattern();

    std::vector<std::string> behaviours;
    std::vector<ScriptBehaviour> scripts;

};

}

#endif // GAMELOGICPATTERN_H
