#pragma once
#include "math\point.h"

class PolygonCollider;
class RayCastHit {
public:
    RayCastHit(Point _origin, Point _intersection, Point _normal, PolygonCollider* other);

    inline Point getIntersection() const { return intersection; }
    inline Point getNormal() const { return normal; }
    inline Point getOrigin() const { return origin; }
    inline double getLength() const { return origin.distanceTo(intersection); }
    inline Point getDirection() const { return intersection - origin; }

    inline PolygonCollider* getOtherCollider() const { return otherCollider; }
private:
    Point origin;
    Point intersection;
    Point normal;

    //The collider we hit
    PolygonCollider *otherCollider;
};