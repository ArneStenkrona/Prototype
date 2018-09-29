#include "polygonCollider.h"
#include <iostream>
#include "System/Physics/physicsEngine.h"
#include <tuple>
#include <algorithm>
#include <cmath>

PolygonCollider::PolygonCollider(GameObject * _object) : Component(_object), isStatic(true), isActive(true)
{
    position = requireComponent<Position>();
    velocity = requireComponent<Velocity>();
     
    //Default shape
    polygon = Rectangular(Point::empty, 32.0, 32.0);

    //Add to physics engine list of all hitboxes
    ALL_COLLIDERS.push_back(this);
}

PolygonCollider::~PolygonCollider()
{
    ALL_COLLIDERS.remove(this);
}

void PolygonCollider::start()
{
}

void PolygonCollider::update()
{
}

void PolygonCollider::updateComponents()
{
    position = (object->hasComponent<Position>()) ? object->getComponent<Position>() : position;
    velocity = (object->hasComponent<Velocity>()) ? object->getComponent<Velocity>() : velocity;
}

void PolygonCollider::setPolygon(Polyshape _polygon)
{
    polygon = _polygon;
}

vector<Collision*> PolygonCollider::calculateCollision(PolygonCollider * a, set<PolygonCollider*>* B)
{
    //Tuple containing time of collision, where 0.0 is the beginning of the frame and 1.0 is the end,
    //And the corresponding collider
    vector<tuple<double, PolygonCollider*>> possibleCollisions = vector<tuple<double, PolygonCollider*>>();
    vector<Collision*> collisions;

    bool collided = false;
 
    for each (PolygonCollider *b in *B) {
        if (a != b) {
            Point colNorm;
            double colTime = 1.0;
            Point relVel = a->relativeVelocity(b);

            if (checkCollision(a, b, colNorm, colTime)) {
                possibleCollisions.push_back({ colTime, b });
                collided = true;
            }
        }
    }
    if (collided) {
        //Sort tuples after earliest collision
        std::sort(begin(possibleCollisions), end(possibleCollisions), [](auto const &t1, auto const &t2) {
            return get<0>(t1) < get<0>(t2);
        });
        
        int i = 0;
        for each (tuple<double, PolygonCollider*> col in possibleCollisions) {
            //Normal of the plane of b that a collides with
            Point collisionNormal;
            //Time of collision, where 0.0 is the beginning of the frame and 1.0 is the end
            double collisionTime = 1.0;
                                   
            if (checkCollision(a, get<1>(col), collisionNormal, collisionTime)) {
                    //Check if A is actually approaching other collider
                    if (a->relativeVelocity(get<1>(col)).normalized().dot(collisionNormal) < 0.000001) {
                    //Velocity required to reach collision
                    const Point velC = a->velocity->velocity * collisionTime;
                    //Overlapping velocity
                    const Point overVel = a->velocity->velocity - velC;

                    const Point correctedVelocity = a->velocity->velocity - collisionNormal * overVel.dot(collisionNormal);

                    //Is it a vertex to vertex collision?
                    bool vToV = false;
                    for (int i = 0; i < a->polygon.numberOfVertices; i++) {
                        Point aVertex = a->polygon.vertices[i] + a->position->position + velC;
                        for (int j = 0; j < get<1>(col)->polygon.numberOfVertices; j++) {
                            Point bVertex = get<1>(col)->polygon.vertices[j] + get<1>(col)->position->position;

                            if ((aVertex).distanceTo(bVertex) < 0.01) {
                                for (int k = 0; k < a->polygon.numberOfVertices; k++) {
                                    if (k != i && (get<1>(col)->polygon.distanceTo(a->polygon.vertices[k] + a->position->position + velC - get<1>(col)->position->position)) >= 0.0001) {
                                        vToV = true;
                                    }
                                }
                            }
                        }
                    }

                    if (!vToV) {
                        Collision *collision = new Collision(a, get<1>(col), collisionNormal, collisionTime);
                        collisions.push_back(collision);

                        if (collisionTime < 0.0) {
                            a->position->position -= collisionNormal * collisionTime;// -0.01 * a->velocity->velocity.normalized();
                            const Point perpNormal = Point(-collisionNormal.y, collisionNormal.x);
                            a->velocity->velocity = a->velocity->velocity.dot(perpNormal) * perpNormal;
                        }
                        else {
                            a->velocity->velocity = correctedVelocity;
                           
                            //const Point perpNormal(-collisionNormal.y, collisionNormal.x);
                            //a->velocity->velocity = a->velocity->velocity.dot(perpNormal) * perpNormal;
                        }
                    }
                    else {
                        if (collisionTime < 0.0) {
                            a->position->position -= collisionNormal * collisionTime -0.01 * a->velocity->velocity.normalized();
                            const Point perpNormal = Point(-collisionNormal.y, collisionNormal.x);
                            a->velocity->velocity = a->velocity->velocity.dot(perpNormal) * perpNormal;
                        }
                    }
                }            
            }
        }
            return collisions;
    }
    return vector<Collision*>();
}

//Courtesy of https://www.codeproject.com/Tips/862988/Find-the-Intersection-Point-of-Two-Line-Segments
bool LineSegementsIntersect(Point p, Point p2, Point q, Point q2,
     Point *intersection, bool considerCollinearOverlapAsIntersect = false)
{
    Point r = p2 - p;
    Point s = q2 - q;
    double rxs = r.cross(s);
    double qpxr = (q - p).cross(r);

    // If r x s = 0 and (q - p) x r = 0, then the two lines are collinear.
    if (abs(rxs) < 0.00000001 && abs(qpxr) < 0.00000001)
    {
        // 1. If either  0 <= (q - p) * r <= r * r or 0 <= (p - q) * s <= * s
        // then the two lines are overlapping,
        if (considerCollinearOverlapAsIntersect)
            if ((0 <= (q - p).dot(r) && (q - p).dot(r) <= r.dot(r) || (0 <= (p - q).dot(s) && (p - q).dot(s) <= s.dot(s))))
                return true;

        // 2. If neither 0 <= (q - p) * r = r * r nor 0 <= (p - q) * s <= s * s
        // then the two lines are collinear but disjoint.
        // No need to implement this expression, as it follows from the expression above.
        return false;
    }

    // 3. If r x s = 0 and (q - p) x r != 0, then the two lines are parallel and non-intersecting.
    if (abs(rxs) < 0.00001 && abs(qpxr) >= 0.00001)
        return false;

    // t = (q - p) x s / (r x s)
    double t = (q - p).cross(s) / rxs;

    // u = (q - p) x r / (r x s)

    double u = (q - p).cross(r) / rxs;

    // 4. If r x s != 0 and 0 <= t <= 1 and 0 <= u <= 1
    // the two line segments meet at the point p + t r = q + u s.
    if (abs(rxs) >= 0.00001 && (0 <= t && t <= 1) && (0 <= u && u <= 1))
    {
        // We can calculate the intersection point using either t or u.
        *intersection = p + t * r;

        // An intersection was found.
        return true;
    }

    // 5. Otherwise, the two line segments are not parallel but do not intersect.
    return false;
}

vector<RayCastHit*> PolygonCollider::checkRayCast(Point a, Point b, set<PolygonCollider*> colliders, std::string message)
{
    vector<RayCastHit*> hits;

    for each (PolygonCollider* col in colliders ){
        const Point * colV = &col->polygon.vertices[0];
        int aNum = col->polygon.numberOfVertices;
        const Point offset = col->position->position;

        double minDistance = DBL_MAX;

        Point intersect;
        Point colPerpNorm;
        bool intersected = false;

        for (int i = 0; i < aNum; i++) {
            Point colA = colV[i] + offset;
            Point colB = colV[(i + 1) % aNum] + offset;
            double ix, iy;
            Point in;
            if (LineSegementsIntersect(a, b, colA, colB, &in, true)) {
            //if (lineIntersect(colA.x, colA.y, colB.x, colB.y,
                //a.x, a.y, b.x, b.y, ix, iy)) {
                intersected = true;
                //Point in = Point(ix, iy);

                double dist = in.distanceTo(a);
                if (dist < minDistance) {
                    minDistance = dist;
                    intersect = in;
                    colPerpNorm = colA - colB;
                }
            }
        }
        if (intersected) {
            Point normal = Point(-colPerpNorm.y, colPerpNorm.x).normalized();
            if (normal.dot(b - a) > 0) normal = Point::empty - normal;
            hits.push_back(new RayCastHit(a, intersect, normal, col, message));
        }
    }
    //Sort after earliest collision
    std::sort(begin(hits), end(hits), [](RayCastHit* const t1, RayCastHit* const t2) {
        return t1->getLength() < t2->getLength();
    });
    return hits;
}

void PolygonCollider::addToMask(unsigned int maskLayer)
{
    addToMaskLayer(this, maskLayer);
}

void PolygonCollider::removeFromMask(unsigned int maskLayer)
{
    removeFromMaskLayer(this, maskLayer);
}


//Algorithm courtesy of PollyColly
//A tutorial can be found here: https://github.com/kirbysayshi/oli-demos/blob/master/Polycolly/docs/html/2D%20polygon.htm
bool PolygonCollider::checkCollision(PolygonCollider *colA, PolygonCollider *colB, Point & _collisionNormal, double & _collisionTime)
{
    /*checkCollision(&a->polygon.vertices[0], a->polygon.numberOfVertices,
        &b->polygon.vertices[0], b->polygon.numberOfVertices,
        a->position->position - b->position->position,
        relVel*/


    const Point * a = &colA->polygon.vertices[0];
    int aNum = colA->polygon.numberOfVertices;
    const Point * b = &colB->polygon.vertices[0];
    int bNum = colB->polygon.numberOfVertices;
    const Point & xOffset = colA->position->position - colB->position->position;
    const Point & xVel = colA->relativeVelocity(colB);

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
    if (fVel2 > 0.0) //Used to be (fVel2 >  0.00001)
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

    if (_collisionNormal.x * xOffset.x + _collisionNormal.y * xOffset.y < 0.0) {
        _collisionNormal *= -1.0;
    }

    return true;
}
//Find minimum translation distance
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
        if (fabs(v) == 0.0) {// 0.0000001) {
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

Point PolygonCollider::relativeVelocity(PolygonCollider *other) const
{
    if (isStatic && other->isStatic) return Point::empty;

    if (other->isStatic) return velocity->velocity;
    if (isStatic) return Point(0,0) - other->velocity->velocity;

    return velocity->velocity - other->velocity->velocity;
}

void PolygonCollider::setActive(bool b)
{
    isActive = b;
}

void PolygonCollider::setStatic(bool b)
{
    isStatic = b;
}
