#include "objectPool.h"
#include <iostream>

std::map<std::string, std::list<GameObject*>> ObjectPool::pool = std::map<std::string, std::list<GameObject*>>();

GameObject * ObjectPool::instantiate(std::string objectName)
{
    if (pool.find(objectName) == pool.end()) {
        std::cout << "Could not instatiate: Object Pool has no container for GameObjects with name \""
            << objectName << " \" "<< std::endl;
        return nullptr;
    }
    if (pool[objectName].size() > 0) {
        GameObject* obj;
        obj = pool[objectName].front();
        pool[objectName].pop_front();
        obj->setActive(true);
        return obj;
    }
    std::cout << "Could not instatiate:  Object Pool has run out of GameObjects with name \""
        << objectName << "\"" << std::endl;
    return nullptr;
}

GameObject * ObjectPool::instantiate(std::string objectName, std::vector<double> args)
{
    GameObject* obj = instantiate(objectName);
    if (obj) {
        obj->setArgs(args);
    }

    return obj;
}

void ObjectPool::repool(GameObject* obj)
{
    if (pool.find(obj->getName()) == pool.end()) {
        std::cout << "Could not repool: Object Pool has no container for GameObjects with name \""
            << obj->getName() << " \" " << std::endl;
        return;
    }
    obj->setActive(false);
    pool[obj->getName()].push_back(obj);
}

void ObjectPool::addToPool(Prefabrication* obj, unsigned int amount)
{
    for (int i = 0; i < amount; i++) {
        GameObject* ob = obj->instantiate();
        ob->setActive(false);
        pool[ob->getName()].push_back(ob);
    }
}

void ObjectPool::clearFromPool(std::string objectName)
{
    pool.erase(objectName);
}
