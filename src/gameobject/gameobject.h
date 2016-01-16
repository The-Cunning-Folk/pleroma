#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<componentloader.h>
#include<vector>
#include<memory>
#include<map>

namespace BQ{
class GameObject
{
public:
    GameObject();

    int transform;

    ComponentLoader * componentLoader;

    std::string name;
    int uniqueId;

    void addComponent(Component&);
    void addComponent(std::string,Component&);

    Transform & loadTransform();
    std::vector<int> loadComponents(std::string);
    int getTransform() const;
    void setTransform(int value);

    ComponentLoader *getComponentLoader() const;
    void setComponentLoader(ComponentLoader *value);

    std::map<std::string, std::map<std::string, int> > getComponents() const;

    std::map<std::string,std::map<std::string,int>> components;

private:



};
}

#endif // GAMEOBJECT_H
