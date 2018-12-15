#pragma once
//Class for objects that can be placed in the game
//Useful abstraction for editor
#include "GameObject\Prefabrications\prefabrication.h"
#include <tuple>
#include <vector>

class Object {
public:
    //Predefined
    static const Object objects[256];

    //Instantiate prefab
    //A parameter vector can be provided
    //The vector will be flattened to a single string and sent to the prefab
    //The vector size should match the paramer names vector size
    GameObject* instantiate(std::vector<std::string> parameters = {}) const;

    //Returns a vector containing the names of all parameters
    inline std::vector<std::string> getParameterNames() const { return parameterNames; }

    ~Object();
private:
    Object(Prefabrication* _prefab, std::vector<std::string> _parameterNames = {});
    Object();
    Prefabrication* prefab;

    //Vector of all parameters
    //Parameters are stored in a tuple consisting of (paramerern name, paramater value)
    //std::vector<std::tuple<std::string, std::string>> parameters;

    //Name of all the parameters
    std::vector<std::string> parameterNames;
};
