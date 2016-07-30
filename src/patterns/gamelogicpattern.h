#ifndef GAMELOGICPATTERN_H
#define GAMELOGICPATTERN_H

#include <factorypattern.h>

namespace BQ
{

class GameLogicPattern : public FactoryPattern
{
public:
    GameLogicPattern();

    std::vector<std::string> behaviours;

};

}

#endif // GAMELOGICPATTERN_H
