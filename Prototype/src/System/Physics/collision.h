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

    inline PolygonCollider * getCollider() const { return collider; }
    inline PolygonCollider * getOtherCollider() const { return otherCollider; }
    inline const std::string getOtherName() const { return otherName; }

    //Returns the velocity required for our collider
    //to hit other within this frame
    Point correctedVelocity();

    //Returns the same collision but from otherColliders perspective
    Collision complement();

private:
    //Our collider
    PolygonCollider * collider;
    //The collider we hit
    PolygonCollider *otherCollider;
    //Name of the gameObject we hit
    const std::string otherName;
};