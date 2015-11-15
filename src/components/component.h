#ifndef COMPONENT_H
#define COMPONENT_H

#include<string>


class Component
{
public:
    Component();

    std::string name; //name of the component. All components should be named
    std::string typeId; //what type of component am I?
    int uniqueId; //a unique component id... not sure how I'll track this but we'll try
};

#endif // COMPONENT_H
