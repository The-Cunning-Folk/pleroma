#ifndef SCRIPTBEHAVIOUR_H
#define SCRIPTBEHAVIOUR_H

#include<vector>
#include<string>

class ScriptBehaviour
{
public:
    ScriptBehaviour();
    ScriptBehaviour(std::string,std::string);

    std::string file;
    std::string instance;
    std::string table;
};

#endif // SCRIPTBEHAVIOUR_H
