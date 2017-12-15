#include "position.h"
#include "GameObject/gameObject.h"


Position::Position(GameObject *_object) : position(Point(0, 0)), Component(_object)
{
}

Position::Position(GameObject *_object, Point _position) : position(_position), Component(_object)
{
}
