#include "object.h"
#include "GameObject\Prefabrications\prefabrications.h"
#include "System\graphics\textureManager.h"

const Object Object::objects[256] = { Object(new GlassContainer()),
                                      Object(new DoorPrefab())
};

GameObject * Object::instantiate() const
{
    return prefab->instantiate();
}

Object::~Object()
{
    delete prefab;
}

Object::Object()
    : prefab(new Prefabrication("NULL"))
{
}

Object::Object(Prefabrication* _prefab)
    : prefab(_prefab)
{
}
