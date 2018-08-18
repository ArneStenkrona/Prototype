#include "collision.h"
#include "GameObject\Component\geometry\polygonCollider.h"

//All ongoing collisions
std::map<const PolygonCollider*, std::set<Collision*>> Collision::ongoingCollisions;
//All collisions from previous frame
std::map<const PolygonCollider*, std::set<Collision*>> Collision::previousFrameCollisions;

Collision::Collision(PolygonCollider * col, PolygonCollider *otherCol, Point colN, double colT) : 
collider(col), otherCollider(otherCol), collisionNormal(colN), collisionTime(colT)
{
    deleteCollision(col, otherCol);
    ongoingCollisions[col].insert(this);
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

/*void Collision::addCollision(PolygonCollider * col, PolygonCollider * otherCol, Point colN, double colT)
{
    deleteCollision(col, otherCol);
    ongoingCollisions[col].insert(new Collision(col, otherCol, colN, colT));
}*/

void Collision::deleteCollision(PolygonCollider * col, PolygonCollider * otherCol)
{
    std::set<Collision*>::iterator it = ongoingCollisions[col].begin();
    while (it != ongoingCollisions[col].end()) {
        if ((*it)->otherCollider == otherCol) {
            ongoingCollisions[col].erase(it);
        }
        ++it;
    }
}

Collision * Collision::getCollision(PolygonCollider * col, PolygonCollider * otherCol)
{
    std::set<Collision*>::iterator it = ongoingCollisions[col].begin();
    while (it != ongoingCollisions[col].end()) {
        if ((*it)->otherCollider == otherCol) {
            return *it;
        }
        ++it;
    }
    return nullptr;
}

void Collision::clearCollisions()
{
    previousFrameCollisions = ongoingCollisions;
    ongoingCollisions.clear();
}

Collision * Collision::getPreviousCollision(PolygonCollider * col, PolygonCollider * otherCol)
{
    std::set<Collision*>::iterator it = previousFrameCollisions[col].begin();
    while (it != previousFrameCollisions[col].end()) {
        if ((*it)->otherCollider == otherCol) {
            return *it;
        }
        ++it;
    }
    return nullptr;
}

set<Collision*> Collision::getOngoingCollisions(PolygonCollider *col)
{
    return ongoingCollisions[col];
}

set<Collision*> Collision::getPreviousFrameCollisions(PolygonCollider *col)
{
    return previousFrameCollisions[col];
}
