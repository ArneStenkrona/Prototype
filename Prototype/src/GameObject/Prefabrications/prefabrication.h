#pragma once
#include "GameObject\gameObject.h"

class Prefabrication {
public:
    Prefabrication(std::string _name);
    virtual GameObject* instantiate();
protected:
    std::string name;
};