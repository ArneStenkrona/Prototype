#include "object.h"
#include "GameObject\Prefabrications\prefabrications.h"
#include "System\graphics\textureManager.h"
#include "tools\stringTools.h"

const Object Object::objects[256] = { Object("CONTAINER", new GlassContainer()),
                                      Object("DOOR", new DoorPrefab(), {"DESTINATION FILEPATH", "DESTINATION COORDINATE X", "DESTINATION COORDINATE Y"})
};

GameObject * Object::instantiate(std::vector<std::string> parameters) const
{
    return prefab->instantiate(parameters);
}

Object::~Object()
{
    delete prefab;
}

Object::Object(std::string _name, Prefabrication* _prefab, std::vector<std::string> _parameterNames)
    : name(_name), prefab(_prefab), parameterNames(_parameterNames)
{
}
