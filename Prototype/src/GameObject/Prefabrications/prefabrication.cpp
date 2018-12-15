#include "prefabrication.h"

Prefabrication::Prefabrication(std::string _name) 
    : name(_name)
{
}

GameObject * Prefabrication::instantiate(std::string parameters) const
{
    return new GameObject(name);
}
