#pragma once
#include "../component.h"
#include "math/polygon.h"
#include "math/rectangle.h"
#include "velocity.h"
#include "System/game/gameLogic.h"
#include <vector>
#include "System\Physics\rayCastHit.h"

//Polygon collider uses a convex polygon for hit detection
//This uses seperation axis method of collision testing
class PolygonCollider : public Component {

public:
    PolygonCollider(GameObject *_object);
    ~PolygonCollider();

    void start();
    void update();
    void updateComponents();

    //getters for the dimensions of the shape
    inline double getWidth() const { return polygon._width; }
    inline double getHeight() const { return polygon._height; }
    //getter for position
    inline Point getPosition() const { return position->position; }

    //getter for velocity
    inline Point getVelocity() const { return velocity->velocity; }

    //returns true if active and gameObject is active
    inline bool getActive() const { return isActive && object->getActive(); }
    //sets active
    void setActive(bool b);

    //returns true if active and gameObject is active
    inline bool getStatic() const { return isStatic; }
    //sets static
    void setStatic(bool b);

    //Set the polygon used for hit detection
    void setPolygon(Polyshape _polygon);
    inline Polyshape getPolygon() const { return polygon; }

    //Collision test
    static bool checkCollision(PolygonCollider *a, PolygonCollider *b, Point& n, double &t);
    //Checks collision between nonstatic collider a and every collider in b
    //Collision is passed by reference and gives a collision-object with the collision data
    static vector<Collision*> calculateCollision(PolygonCollider *a, set<PolygonCollider*> *b);

    //Checks if raycast hits any of colliders
    //Returns a vector of rayCastHits sorted by distance from a
    static vector<RayCastHit*> checkRayCast(Point a, Point b, set<PolygonCollider*> colliders);

    void addToMask(unsigned int maskLayer);
    void removeFromMask(unsigned int maskLayer);

private:

    //Find the minimum translation distance
    static bool findMTD(Point* xAxis, double* taxis, int iNumAxes, Point& n, double& t);
    //calculate the projection range of a polygon along an axis
    static void getInterval(const Point *axVertices, int iNumVertices, const Point& xAxis, double& min, double& max);

    static bool intervalIntersect(const Point* A, int Anum,
        const Point* B, int Bnum,
        const Point& xAxis,
        const Point& xOffset, const Point& xVel,
        double& taxis, double tmax);

    Polyshape polygon;
    //Returns velocity relative to other
    Point relativeVelocity(PolygonCollider *other) const;
    
    //Determines wether the hitbox is active
    bool isActive;
    //Determines if the hitbox has velocity, and therefore will be affected by response
    bool isStatic;

    //Position and velocity components
    Position *position;
    Velocity *velocity;
};