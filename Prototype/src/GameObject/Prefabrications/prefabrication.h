#pragma once
#include "GameObject\gameObject.h"

class Prefabrication {
public:
    Prefabrication(std::string _name);
    virtual GameObject* instantiate(std::vector<std::string> parameters = {}) const;
protected:
    std::string name;
};