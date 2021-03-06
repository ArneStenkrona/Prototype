#include "quadTree.h"
#include <iostream>
#include "System\graphics\graphicsEngine.h"
#include <math.h>

QuadTree::QuadTree(int pLevel, Point _position, Point _bounds) : level(pLevel), position(_position), bounds(_bounds)
{
}

QuadTree::~QuadTree()
{
    clear();
}

void QuadTree::clear()
{
    colliders.clear();

    for (int i = 0; i < sizeof(nodes)/sizeof(*nodes); i++) {
        if (nodes[i] != nullptr) {
            nodes[i]->clear();
            delete nodes[i];
            nodes[i] = nullptr;
        }

    }
}

void QuadTree::split()
{

    //New nodes should be half the dimensions
    double subWidth = bounds.x / 2;
    double subHeight = bounds.y / 2;

    double x = position.x;
    double y = position.y;

    //The subnodes
    nodes[0] = new QuadTree(level + 1, Point(x + subWidth, y), Point(subWidth, subHeight));
    nodes[1] = new QuadTree(level + 1, Point(x, y), Point(subWidth, subHeight));
    nodes[2] = new QuadTree(level + 1, Point(x, y + subHeight), Point(subWidth, subHeight));
    nodes[3] = new QuadTree(level + 1, Point(x + subWidth, y + subHeight), Point(subWidth, subHeight));


        std::set<PolygonCollider*>::iterator it;
        for (it = colliders.begin(); it != colliders.end(); ) {
            int index = getIndex(*it);
            if (index > -1) {
                nodes[index]->insert(*it);
                colliders.erase(it++);
            }
            else {
                switch (index) {
                case -1:
                    nodes[0]->insert(*it);
                    nodes[1]->insert(*it);
                    nodes[2]->insert(*it);
                    nodes[3]->insert(*it);
                    break;
                case -2:
                    nodes[0]->insert(*it);
                    nodes[1]->insert(*it);
                    break;
                case -3:
                    nodes[2]->insert(*it);
                    nodes[3]->insert(*it);
                    break;
                case -4:
                    nodes[0]->insert(*it);
                    nodes[3]->insert(*it);
                    break;
                case -5:
                    nodes[1]->insert(*it);
                    nodes[2]->insert(*it);
                    break;

                }
                it++;
            }
        }
        colliders.clear();
}

set<PolygonCollider*>* QuadTree::retrieve(set<PolygonCollider*> *returnColliders, PolygonCollider *collider)
{
    int index = getIndex(collider);
    if (index > -1 && nodes[0] != nullptr) {
        nodes[index]->retrieve(returnColliders, collider);
    }
    else if (nodes[0] != nullptr)//If collider does not fit into the node, get all of the children 
    {
        switch (index) {
            case -1:
                for (int i = 0; i < sizeof(nodes) / sizeof(*nodes); i++) {
                    nodes[i]->retrieve(returnColliders, collider);
                }
            case -2:
                nodes[0]->retrieve(returnColliders, collider);
                nodes[1]->retrieve(returnColliders, collider);
                break;
            case -3:
                nodes[2]->retrieve(returnColliders, collider);
                nodes[3]->retrieve(returnColliders, collider);
                break;
            case -4:
                nodes[0]->retrieve(returnColliders, collider);
                nodes[3]->retrieve(returnColliders, collider);
                break;
            case -5:
                nodes[1]->retrieve(returnColliders, collider);
                nodes[2]->retrieve(returnColliders, collider);
                break;
        }
    }
    if (nodes[0] == nullptr) {
        returnColliders->insert(colliders.begin(), colliders.end());
    }
    return returnColliders;
}

inline bool segmentIntersectRectangle(double a_rectangleMinX,
    double a_rectangleMinY,
    double a_rectangleMaxX,
    double a_rectangleMaxY,
    double a_p1x,
    double a_p1y,
    double a_p2x,
    double a_p2y)
{
    // Find min and max X for the segment

    double minX = a_p1x;
    double maxX = a_p2x;

    if (a_p1x > a_p2x)
    {
        minX = a_p2x;
        maxX = a_p1x;
    }

    // Find the intersection of the segment's and rectangle's x-projections

    if (maxX > a_rectangleMaxX)
    {
        maxX = a_rectangleMaxX;
    }

    if (minX < a_rectangleMinX)
    {
        minX = a_rectangleMinX;
    }

    if (minX > maxX) // If their projections do not intersect return false
    {
        return false;
    }

    // Find corresponding min and max Y for min and max X we found before

    double minY = a_p1y;
    double maxY = a_p2y;

    double dx = a_p2x - a_p1x;

    if (std::abs(dx) > 0.0000001)
    {
        double a = (a_p2y - a_p1y) / dx;
        double b = a_p1y - a * a_p1x;
        minY = a * minX + b;
        maxY = a * maxX + b;
    }

    if (minY > maxY)
    {
        double tmp = maxY;
        maxY = minY;
        minY = tmp;
    }

    // Find the intersection of the segment's and rectangle's y-projections

    if (maxY > a_rectangleMaxY)
    {
        maxY = a_rectangleMaxY;
    }

    if (minY < a_rectangleMinY)
    {
        minY = a_rectangleMinY;
    }

    if (minY > maxY) // If Y-projections do not intersect return false
    {
        return false;
    }

    return true;
}
set<PolygonCollider*>* QuadTree::retrieve(set<PolygonCollider*>* returnColliders, Point a, Point b)
{
    bool quadrants[] = { false,false,false,false };
    quadrants[0] = segmentIntersectRectangle(position.x + (bounds.x / 2), position.y, position.x + (bounds.x / 2), position.y + (bounds.y / 2),
        a.x, a.y, b.x, b.y);
    quadrants[1] = segmentIntersectRectangle(position.x, position.y, position.x + (bounds.x / 2), position.y + (bounds.y / 2),
        a.x, a.y, b.x, b.y);
    quadrants[2] = segmentIntersectRectangle(position.x, position.y + (bounds.y / 2), position.x + (bounds.x / 2), position.y + (bounds.y / 2),
        a.x, a.y, b.x, b.y);
    quadrants[3] = segmentIntersectRectangle(position.x + (bounds.x / 2), position.y + (bounds.y / 2), position.x + (bounds.x / 2), position.y + (bounds.y / 2),
        a.x, a.y, b.x, b.y);

    if (nodes[0] != nullptr) {
        for (int i = 0; i < 4; i++) {
            //if (true || quadrants[i])
            //{
                nodes[i]->retrieve(returnColliders, a, b);
            //}
        }
    }
      
    bool overlap = segmentIntersectRectangle(position.x, position.y, position.x + bounds.x, position.y + bounds.y,
    a.x, a.y, b.x, b.y);


    if (overlap) {
        //returnColliders->reserve(returnColliders->size() + colliders.size());
        returnColliders->insert(colliders.begin(), colliders.end());
    }

    return returnColliders;
}

void QuadTree::insert(PolygonCollider * collider)
{
    if (nodes[0] != nullptr) {
        int index = getIndex(collider);
        if (index > -1) {
            nodes[index]->insert(collider);
            return;
        }
        else {
            switch (index) {
            case -1:
                nodes[0]->insert(collider);
                nodes[1]->insert(collider);
                nodes[2]->insert(collider);
                nodes[3]->insert(collider);
                break;
            case -2:
                nodes[0]->insert(collider);
                nodes[1]->insert(collider);
                break;
            case -3:
                nodes[2]->insert(collider);
                nodes[3]->insert(collider);
                break;
            case -4:
                nodes[0]->insert(collider);
                nodes[3]->insert(collider);
                break;
            case -5:
                nodes[1]->insert(collider);
                nodes[2]->insert(collider);
                break;
            case -6:
                return;
            }
        }
    }
    colliders.insert(collider);
    if (nodes[0] == nullptr && colliders.size() > Max_Objects && level < Max_Levels) {
            split();
    }
}


void QuadTree::setBounds(Point _bounds)
{
    bounds = Point(_bounds.x, _bounds.y);
}

void QuadTree::draw()
{
    Point camPos = Renderer::getCameraPosition();
    
    SDL_Rect outlineRect = { (int)(position.x - camPos.x), (int)(position.y - camPos.y), (int)bounds.x, (int)bounds.y };

    SDL_SetRenderDrawColor(GraphicsEngine::getActiveRenderer(), 0x00, 0x00, 0xFF, 0x00);
    SDL_RenderDrawRect(GraphicsEngine::getActiveRenderer(), &outlineRect);
    if (nodes[0] != nullptr) {
        for (int i = 0; i < 4; i++) {
            nodes[i]->draw();
        }
    }
}

int QuadTree::getIndex(PolygonCollider * collider)
{
    int index = -1;

    double verticalMidpoint = position.x + (bounds.x / 2);
    double horizontalMidpoint = position.y + (bounds.y / 2);

    //Position of the box
    Point colliderPos = collider->getEffectiveOrigin();
    //dimensions of the box
    Point colliderDimensions;

    //if the collider is nonstatic, account for velocity
    if (collider->getStatic()) {
        colliderDimensions = Point(collider->getWidth(), collider->getHeight());
    }
    else {
        Point vel = collider->getVelocity();
        colliderDimensions = Point(collider->getWidth() + fabs(vel.x), collider->getHeight() + fabs(vel.y));

        //Account for the direction of the velocity
        if (vel.x < 0.0) {
            colliderPos = colliderPos + Point(vel.x, 0.0);
        }

        if (vel.y < 0.0) {
            colliderPos = colliderPos + Point(0.0, vel.y);
        }

    }

    //Object can completely fit within the top quadrants
    bool topQuadrant = (colliderPos.y + colliderDimensions.y < horizontalMidpoint);
    //Object can completely fit within the bottom quadrants
    bool bottomQuadrant = (colliderPos.y > horizontalMidpoint);
    //Object can completely fit within the left quadrants
    bool leftQuadrant = (colliderPos.x + colliderDimensions.x < verticalMidpoint);
    //Object can completely fit within the right quadrants
    bool rightQuadrant = (colliderPos.x > verticalMidpoint);

    //Object can completely fit within the left quadrants
    if (leftQuadrant) {
        if (topQuadrant) {
            index = 1;
        }
        else if (bottomQuadrant) {
            index = 2;
        }
    }
    //Object can completely fit within the right quadrants
    else if (rightQuadrant) {
        if (topQuadrant) 
            index = 0;
        else if (bottomQuadrant)
            index = 3;
    }
    else {
        //both top quadrants
        if (topQuadrant && !leftQuadrant)
            index = -2;
        //both bottom quadrants
        if (bottomQuadrant && !leftQuadrant)
            index = -3;
        //both left quadrants
        if (leftQuadrant && !bottomQuadrant)
            index = -4;
        //both right quadrants
        if (rightQuadrant && !bottomQuadrant)
            index = -5;
    }

    return index;
}
