#pragma once
#include "math\point.h"
#include <map>
#include <set>

//This class contains information about a collision between two colliders
class PolygonCollider;
class Collision {
public:
    Collision(PolygonCollider *col, PolygonCollider *otherCol, Point colN, double colT);

    //Normal of the collided surface
    Point collisionNormal;
    //Time (as subdivision of a frame) until hit
    const double collisionTime;

    PolygonCollider * getCollider();
    PolygonCollider * getOtherCollider();

    //Returns the velocity required for our collider
    //to hit other within this frame
    Point correctedVelocity();

private:
    //Our collider
    PolygonCollider * collider;
    //The collider we hit
    PolygonCollider *otherCollider;

    //All ongoing collisions
    static std::map<const PolygonCollider*, std::set<Collision*>> ongoingCollisions;
    //All collisions from previous frame
    static std::map<const PolygonCollider*, std::set<Collision*>> previousFrameCollisions;
};