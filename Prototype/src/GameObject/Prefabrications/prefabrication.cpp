#include "prefabrication.h"

Prefabrication::Prefabrication(std::string _name) 
    : name(_name)
{
}

GameObject * Prefabrication::instantiate()
{
    return new GameObject(name);
}
