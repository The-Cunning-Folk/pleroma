#ifndef LOGICENGINE_H
#define LOGICENGINE_H

#include<engine.h>
#include <gamelogic.h>
#include <behaviour.h>

namespace BQ{

class Behaviour;

typedef std::unique_ptr<Behaviour> logicUnit; // the unique pointer object to a behavioural unit


class LogicEngine : public Engine
{

public:

    std::vector<logicUnit> behaviours;

    Behaviour& bindBehaviour(GameLogic &, std::string);

    Behaviour& getBehaviour(int);

    LogicEngine();
};
}

#endif // LOGICENGINE_H
