#include "rayCastHit.h"
#include "GameObject\Component\geometry\polygonCollider.h"

RayCastHit::RayCastHit(Point _origin, Point _intersection, Point _normal, PolygonCollider* other)
    : RayCastHit(_origin, _intersection, _normal, other, "")
{
}

RayCastHit::RayCastHit(Point _origin, Point _intersection, Point _normal, PolygonCollider * other, const std::string &_message)
    : origin(_origin), intersection(_intersection), normal(_normal), otherCollider(other), message(_message)
{
}
