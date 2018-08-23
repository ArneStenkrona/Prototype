#include "collision.h"
#include "GameObject\Component\geometry\polygonCollider.h"

Collision::Collision(PolygonCollider * col, PolygonCollider *otherCol, Point colN, double colT) : 
collider(col), otherCollider(otherCol), collisionNormal(colN), collisionTime(colT)
{
}

PolygonCollider * Collision::getCollider()
{
    return collider;
}

PolygonCollider * Collision::getOtherCollider()
{
    return otherCollider;
}

Point Collision::correctedVelocity()
{
    //Velocity required to reach collision
    Point velC = collider->getVelocity() * collisionTime;
    //Overlapping velocity
    Point overVel = collider->getVelocity() - velC;
    Point correctedVelocity = collider->getVelocity() - collisionNormal * overVel.dot(collisionNormal);
    return correctedVelocity;
}
