#include "object.h"
#include "GameObject\Prefabrications\prefabrications.h"
#include "System\graphics\textureManager.h"
#include "tools\stringTools.h"

const Object Object::objects[256] = { Object(new GlassContainer()),
                                      Object(new DoorPrefab(), {"Door ID","Destination filepath"})
};

GameObject * Object::instantiate(std::vector<std::string> parameters) const
{
    return prefab->instantiate(flattenStringVector(parameters));
}

Object::~Object()
{
    delete prefab;
}

Object::Object()
    : prefab(new Prefabrication("NULL"))
{
}

Object::Object(Prefabrication* _prefab, std::vector<std::string> _parameterNames)
    : prefab(_prefab)
{
}
