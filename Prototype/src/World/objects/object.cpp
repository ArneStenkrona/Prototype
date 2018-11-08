#include "object.h"
#include "GameObject\Prefabrications\prefabrications.h"

const Object Object::objects[256] = { GlassContainer()
};

GameObject * Object::instantiate() const
{
    return prefab.instantiate();
}

Object::Object()
    : prefab(Prefabrication("NULL"))
{
}

Object::Object(Prefabrication _prefab)
    : prefab(_prefab)
{
}
