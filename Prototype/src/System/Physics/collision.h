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

    //Adds entry to ongoing collisions container
    //static void addCollision(PolygonCollider *col, PolygonCollider *otherCol, Point colN, double colT);
    //Deletes entry in ongoing collisions container
    static void deleteCollision(PolygonCollider *col, PolygonCollider *otherCol);
    //Gets entry from ongoing collisions container, returns null if not there
    static Collision * getCollision(PolygonCollider *col, PolygonCollider *otherCol);
    //Clears ongoing collisions container
    static void clearCollisions();
    //Gets entry from previous frame
    static Collision * getPreviousCollision(PolygonCollider *col, PolygonCollider *otherCol);
    //Returns ongoing collisions involving col
    static std::set<Collision*> getOngoingCollisions(PolygonCollider *col);
    //Returns previous frame collisions involving col
    static std::set<Collision*> getPreviousFrameCollisions(PolygonCollider *col);


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