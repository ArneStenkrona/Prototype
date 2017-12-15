#pragma once
#include "../component.h"
#include "math/polygon.h"
#include "math/rectangle.h"
#include "velocity.h"
#include "System/gameLogic.h"
#include <vector>

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
    double getWidth();
    double getHeight();
    //getter for position
    Point getPosition();

    //getter for velocity
    Point getVelocity();

    //returns true if active and gameObject is active
    bool getActive();
    //sets active
    void setActive(bool b);

    //returns true if active and gameObject is active
    bool getStatic();
    //sets static
    void setStatic(bool b);

    //Set the polygon used for hit detection
    void setPolygon(Polygon _polygon);
    Polygon getPolygon();

    //Sets the flags for this tile
    void setFlags(bool _up, bool _right, bool _left, bool _down);

    static bool calculateCollision(PolygonCollider a, PolygonCollider b);

private:


    //Generate the separation axis that needs to be tested
    //static bool intersect(PolygonCollider a, PolygonCollider b, Point &mtd);

    //Calculates the intervals of each polygon along the seperation plan normal
    //static void calculateInterval(Point axis, Shape p, double &min, double &max);
    //Seperates the polygons
    //static bool axisSeperatePolygons(Point& axis, Shape a, Shape b, Point offset, Point vel, double& t, double tmax);



    //Collision test
    static bool collide(const Point *a, int aNum,
        const Point *b, int bNum,
        const Point &xOffset, const Point &xVel,
        Point& n, double &t);
    //Find the minimum translation distance
    static bool findMTD(Point* xAxis, double* taxis, int iNumAxes, Point& n, double& t);
    //calculate the projection range of a polygon along an axis
    static void getInterval(const Point *axVertices, int iNumVertices, const Point& xAxis, double& min, double& max);

    static bool intervalIntersect(const Point* A, int Anum,
        const Point* B, int Bnum,
        const Point& xAxis,
        const Point& xOffset, const Point& xVel,
        double& taxis, double tmax);

    Polygon polygon;

    //Tile flags. Tells us wether this tile is connected to another tile in either of the four directions
    bool up;
    bool right;
    bool left;
    bool down;

    //Determines wether the hitbox is active
    bool isActive;
    //Determiens wether the hitbox has velocity, and therefore will be affected by response
    bool isStatic;

    //Position and velocity components
    Position *position;
    Velocity *velocity;

};