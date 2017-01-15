#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<componentloader.h>
#include<vector>
#include<memory>
#include<map>

namespace BQ{

typedef std::map<std::string,std::map<std::string,int>>::iterator it_complist;
typedef std::map<std::string,int>::iterator it_component;

class GameObject
{
public:
    GameObject();

    int transform;

    std::string name;
    std::string level;
    int uniqueId;

    bool active;

    void deactivate();
    void activate();

    void addComponent(Component&);
    void addComponent(std::string,Component&);

    int getTransform() const;
    void setTransform(int value);

    std::map<std::string, std::map<std::string, int> > getComponents() const;

    std::map<std::string,std::map<std::string,int>> components;

private:



};
}

#endif // GAMEOBJECT_H
