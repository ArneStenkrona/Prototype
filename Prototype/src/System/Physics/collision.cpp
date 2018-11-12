#include "collision.h"
#include "GameObject\Component\geometry\polygonCollider.h"

Collision::Collision(PolygonCollider * col, PolygonCollider *otherCol, Point colN, double colT) 
    : collider(col), otherCollider(otherCol), collisionNormal(colN), collisionTime(colT),
      otherName(otherCol->getGameObject()->getName())
    
{
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

Collision Collision::complement()
{
    return Collision(otherCollider, collider, -1  * collisionNormal, collisionTime);
}
