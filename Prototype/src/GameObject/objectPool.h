#pragma once
#include <map>
#include <list>
#include <string>
#include <vector>
#include "gameObject.h"
#include "Prefabrications\prefabrication.h"

//Pooling class to avoid dynamic object creation at runtime
class ObjectPool {
public:
    static GameObject* instantiate(std::string objectName);
    static GameObject* instantiate(std::string objectName, std::vector<double> args);
    static void repool(GameObject* obj);
    static void addToPool(Prefabrication* obj, unsigned int amount = 1);
    //Removes pool container and deletes objects of name objectName
    static void clearFromPool(std::string objectName);
private:
    static std::map<std::string, std::list<GameObject*>> pool;
};