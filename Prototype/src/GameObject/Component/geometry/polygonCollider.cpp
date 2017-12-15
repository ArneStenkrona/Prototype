#include "polygonCollider.h"
#include <iostream>
#include "System/Physics/physicsEngine.h"

PolygonCollider::PolygonCollider(GameObject * _object) : Component(_object), isStatic(true), isActive(true)
{
    //Check for position component
    if (object->hasComponent<Position>()) {
        position = object->getComponent<Position>();
    }
    else {
        position = object->addComponent<Position>();
    }
    //Check for velocity component. !!!This should only be required if hitbox isnt static. Fix this in the future!!!
    if (object->hasComponent<Velocity>()) {
        velocity = object->getComponent<Velocity>();
    }
    else {
        velocity = object->addComponent<Velocity>();
    }

    //Default shape
    //polygon = Triangle(Point(0.0, 32.0), Point(32.0, 0), Point(32.0, 32.0));
    polygon = Rectangular(Point::empty, 32.0, 32.0);
    //polygon = Triangle(Point::empty, Point(32.0, 32.0), Point(32.0, 0));

    //Add to physics engine list of all hitboxes
    ALL_HITBOXES.push_back(this);
}

PolygonCollider::~PolygonCollider()
{
    ALL_HITBOXES.remove(this);
}

void PolygonCollider::start()
{
}

void PolygonCollider::update()
{
}

void PolygonCollider::updateComponents()
{
    //Check for position component
    if (object->hasComponent<Position>()) {
        position = object->getComponent<Position>();
    }

    //Check for velocity component
    if (object->hasComponent<Velocity>()) {
        velocity = object->getComponent<Velocity>();
    }
}

double PolygonCollider::getWidth()
{
    return polygon._width;
}

double PolygonCollider::getHeight()
{
    return polygon._height;
}

Point PolygonCollider::getPosition()
{
    return position->position;
}

Point PolygonCollider::getVelocity()
{
    return velocity->velocity;
}

void PolygonCollider::setPolygon(Polygon _polygon)
{
    polygon = _polygon;
}

Polygon PolygonCollider::getPolygon()
{
    return polygon;
}

void PolygonCollider::setFlags(bool _up, bool _right, bool _left, bool _down)
{
    up = _up;
    right = _right;
    left = _left;
    down = _down;
}

bool PolygonCollider::calculateCollision(PolygonCollider a, PolygonCollider b)
{

    //Normal of the plan of b that a collides with
    Point collisionNormal;
    //Time of collision, where 0.0 is the beginning of the frame and 1.0 is the end
    double collisionTime = 1.0;

    //Relative velocity of a and b
    Point relativeVelocity;

    //Avoids null ptr exception if b is static and doesnt contain velocity component
    if (b.isStatic) {
        relativeVelocity = a.velocity->velocity;
    }
    else {
        relativeVelocity = a.velocity->velocity - b.velocity->velocity;
    }

    //Check if collision occured
    if (collide(&a.polygon.vertices[0], a.polygon.numberOfVertices,
        &b.polygon.vertices[0], b.polygon.numberOfVertices,
        a.position->position - b.position->position,
        relativeVelocity, collisionNormal, collisionTime))
    {

        //Check for tile flags
        if (collisionNormal.x < -0.9 && b.left) {
            return false;
        }
        if (collisionNormal.x > 0.9 && b.right) {
            return false;
        }
        if (collisionNormal.y < -0.9 && b.up) {
            return false;
        }
        if (collisionNormal.y > 0.9 && b.down) {
            return false;
        }

        //collision time less than 0.0 indicates that a and b are already overlapping
        if (collisionTime < 0.0) {
            a.position->position -= collisionNormal * collisionTime;//1.01; //Removed this coefficient as it was causing trouble



                                                                    //THE FOLLOWING CODE WAS COPY-PASTED FROM THE ELSE-IF BRANCH AFTER THIS BRANCH
                                                                    //IT SEEMS TO DO THE JOB BUT I MIGHT WANT TO TWEAK IT. I DON'T KNOW

                                                                    //mSign helps us determine which way to rotate the collisionNormal for proper response
            int mSign = 0.0;

            if (relativeVelocity.x > 0.0) {
                mSign = 1.0;
            }
            else if (relativeVelocity.x < 0.0) {
                mSign = -1.0;
            }


            //velocity remaining after intersection
            Point velC = Point(a.velocity->velocity * (1.0 - collisionTime));
            //normal rotated 90 degrees in suitable direction
            Point normR = Point(-collisionNormal.y, collisionNormal.x) * -mSign;

            double squaredMagnitudeNormR = (normR.x * normR.x + normR.y * normR.y);

            Point afterC;

            //velocity vector adjusted after collision
            if (squaredMagnitudeNormR == 0.0) {
                afterC = Point::empty;
            }
            else {
                afterC = normR * ((velC.x * normR.x + velC.y * normR.y) / (normR.x * normR.x + normR.y * normR.y));
            }

            //velocity of a is deflected
            a.velocity->velocity = a.velocity->velocity * collisionTime + afterC;

            //END OF COPY-PASTED CODE

        }
        //Only perform velocity adjustment if a and be are heading towards eachother
        else if (collisionTime < 1.0 && relativeVelocity.x * collisionNormal.x + relativeVelocity.y * collisionNormal.y < 0.0) {

            //mSign helps us determine which way to rotate the collisionNormal for proper response
            int mSign = 0.0;

            if (relativeVelocity.x > 0.0) {
                mSign = 1.0;
            }
            else if (relativeVelocity.x < 0.0) {
                mSign = -1.0;
            }

            //velocity remaining after intersection
            Point velC = Point(a.velocity->velocity * (1.0 - collisionTime));
            //normal rotated 90 degrees in suitable direction
            Point normR = Point(-collisionNormal.y, collisionNormal.x) * -mSign;

            double squaredMagnitudeNormR = (normR.x * normR.x + normR.y * normR.y);

            Point afterC;

            //velocity vector adjusted after collision
            if (squaredMagnitudeNormR == 0.0) {
                afterC = Point::empty;
            }
            else {
                afterC = normR * ((velC.x * normR.x + velC.y * normR.y) / (normR.x * normR.x + normR.y * normR.y));
            }

            //velocity of a is deflected
            a.velocity->velocity = a.velocity->velocity * collisionTime + afterC;
        }

        return true;
    }

    return false;
}

bool PolygonCollider::collide(const Point * a, int aNum, const Point * b, int bNum, const Point & xOffset, const Point & xVel, Point & _collisionNormal, double & _collisionTime)
{
    if (!a || !b) {
        return false;
    }

    //All of the separation axes
    //Note : a maximum of 32 vertices per poly is supported
    Point xAxis[64];
    double tAxis[64];
    int iNumAxes = 0;


    xAxis[iNumAxes] = Point(-xVel.y, xVel.x);
    double fVel2 = xVel.x * xVel.x + xVel.y * xVel.y;
    if (fVel2 > 0.00001) //I think we are fine if we change this to (fVel2 > 0.0)
    {
        if (!intervalIntersect(a, aNum, b, bNum, xAxis[iNumAxes], xOffset, xVel, tAxis[iNumAxes], _collisionTime)) {
            return false;
        }
        iNumAxes++;
    }

    //test separation of axes of a
    for (int j = aNum - 1, i = 0; i < aNum; j = i, i++) {
        Point e0 = a[j];
        Point e1 = a[i];
        Point e = e1 - e0;
        xAxis[iNumAxes] = Point(-e.y, e.x);

        if (!intervalIntersect(a, aNum, b, bNum, xAxis[iNumAxes], xOffset, xVel, tAxis[iNumAxes], _collisionTime)) {
            return false;
        }
        iNumAxes++;
    }

    //test separation of axes of b
    for (int j = bNum - 1, i = 0; i < bNum; j = i, i++) {
        Point e0 = b[j];
        Point e1 = b[i];
        Point e = e1 - e0;
        xAxis[iNumAxes] = Point(-e.y, e.x);

        if (!intervalIntersect(a, aNum, b, bNum, xAxis[iNumAxes], xOffset, xVel, tAxis[iNumAxes], _collisionTime)) {
            return false;
        }
        iNumAxes++;
    }

    if (!findMTD(xAxis, tAxis, iNumAxes, _collisionNormal, _collisionTime)) {
        return false;
    }

    //make sure the polygons gets pushed away from each other

    if (_collisionNormal.x * xOffset.x + _collisionNormal.y * xOffset.y < 0.0) {
        _collisionNormal *= -1.0;
    }

    return true;
}

bool PolygonCollider::findMTD(Point* xAxis, double* tAxis, int iNumAxes, Point& N, double& t)
{
    //Find collision first
    int mini = -1;
    t = 0.0;
    for (int i = 0; i < iNumAxes; i++) {

        if (tAxis[i] > 0.0) {
            if (tAxis[i] > t) {
                mini = i;
                t = tAxis[i];
                N = xAxis[i];
                N = N.normalized();
            }
        }
    }

    //found one
    if (mini != -1) {
        return true;
    }


    //did not find one, search for overlap
    mini = -1;
    for (int i = 0; i < iNumAxes; i++) {

        double n = xAxis[i].magnitude();

        xAxis[i] = xAxis[i].normalized();
        tAxis[i] /= n;

        if (tAxis[i] > t || mini == -1) {

            mini = i;
            t = tAxis[i];
            N = xAxis[i];
        }
    }

    if (mini == -1)
        printf("Error\n");

    return mini != -1;
}

void PolygonCollider::getInterval(const Point * axVertices, int iNumVertices, const Point & xAxis, double & min, double & max)
{
    min = max = (axVertices[0].x * xAxis.x + axVertices[0].y * xAxis.y);

    for (int i = 1; i < iNumVertices; i++)
    {
        double d = (axVertices[i].x * xAxis.x + axVertices[i].y * xAxis.y);
        if (d < min) min = d; else if (d > max) max = d;
    }
}

bool PolygonCollider::intervalIntersect(const Point * A, int Anum, const Point * B, int Bnum, const Point & xAxis, const Point & xOffset, const Point & xVel, double & taxis, double tmax)
{
    double min0, max0;
    double min1, max1;
    getInterval(A, Anum, xAxis, min0, max0);
    getInterval(B, Bnum, xAxis, min1, max1);

    double h = xOffset.x * xAxis.x + xOffset.y * xAxis.y;
    min0 += h;
    max0 += h;

    double d0 = min0 - max1; //if overlapped, d0 < 0
    double d1 = min1 - max0; //if overlapped d1 > 0

                             //separated, test dynamic intervals
    if (d0 > 0.0 || d1 > 0.0) {

        double v = xVel.x * xAxis.x + xVel.y * xAxis.y;

        //small velocity, so only the overlap test will be relevant
        if (fabs(v) < 0.0000001) {
            return false;
        }

        double t0 = -d0 / v; // time of impact to d0 reaches 0
        double t1 = d1 / v; // time of impact to d0 reaches 1

        if (t0 > t1) {
            double temp = t0;
            t0 = t1;
            t1 = temp;
        }
        taxis = (t0 > 0.0) ? t0 : t1;
        if (taxis < 0.0 || taxis > tmax) {
            return false;
        }

        return true;
    }
    else {
        // overlap. Get the interval, as a the smallest of |d0| and |d1|
        // return negative number to mark it as an overlap
        taxis = (d0 > d1) ? d0 : d1;
        return true;
    }
}

bool PolygonCollider::getActive()
{
    return isActive && object->getActive();
}

void PolygonCollider::setActive(bool b)
{
    isActive = b;
}

bool PolygonCollider::getStatic()
{
    return isStatic;
}

void PolygonCollider::setStatic(bool b)
{
    isStatic = b;
}