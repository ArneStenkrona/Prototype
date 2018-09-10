#include "rayCastHit.h"
#include "GameObject\Component\geometry\polygonCollider.h"

RayCastHit::RayCastHit(Point _origin, Point _intersection, Point _normal, PolygonCollider* other)
    : origin(_origin), intersection(_intersection), normal(_normal), otherCollider(other)
{
}
