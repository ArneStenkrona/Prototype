#pragma once
#include "GameObject\gameObject.h"

class Prefabrication {
public:
    Prefabrication(std::string _name);
    virtual GameObject* instantiate() const;
protected:
    std::string name;
};