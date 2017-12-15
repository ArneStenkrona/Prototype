#include "quadTree.h"
#include <iostream>

QuadTree::QuadTree(int pLevel, Point _position, Point _bounds) : level(pLevel), position(_position), bounds(_bounds)
{
}

QuadTree::~QuadTree()
{
    clear();
}

void QuadTree::clear()
{
    hitBoxes.clear();

    //sizeof(nodes) gave iterator depth level so changed it to 4. Mysterious
    for (int i = 0; i < 4/*sizeof(nodes)*/; i++) {
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
}

vector<PolygonCollider*>* QuadTree::retrieve(vector<PolygonCollider*> *returnColliders, PolygonCollider *collider)
{
    int index = getIndex(collider);
    if (index != -1 && nodes[0] != nullptr) {
        nodes[index]->retrieve(returnColliders, collider);
    }
    else if (nodes[0] != nullptr)//If collider does not fit into the node, get all of the children 
    {
        for (int i = 0; i < 4; i++) {
            nodes[i]->retrieve(returnColliders, collider);
        }
    }

    returnColliders->reserve(returnColliders->size() + hitBoxes.size());
    returnColliders->insert(returnColliders->end(), hitBoxes.begin(), hitBoxes.end());

    return returnColliders;

}

void QuadTree::insert(PolygonCollider * collider)
{

    if (nodes[0] != nullptr) {
        int index = getIndex(collider);

        if (index != -1) {
            nodes[index]->insert(collider);
            return;
        }
    }

    hitBoxes.push_back(collider);

    if (hitBoxes.size() > Max_Objects && level < Max_Levels) {
        if (nodes[0] == nullptr) {
            split();
        }
        int i = 0;
        while (i < hitBoxes.size()) {
            int index = getIndex(hitBoxes[i]);
            if (index != -1) {

                PolygonCollider* temp = hitBoxes[i];
                hitBoxes.erase(hitBoxes.begin() + i);
                nodes[index]->insert(temp);
            }
            else
            {
                i++;
            }

        }

    }
}

void QuadTree::setBounds(Point _bounds)
{

    //x and y appear to be swapped in quadTree class
    //Algorithms should perhaps be rewritten to avoid future bugs
    bounds = Point(_bounds.y, _bounds.x);
}

int QuadTree::getIndex(PolygonCollider * collider)
{
    int index = -1;

    double verticalMidpoint = position.x + (bounds.x / 2);
    double horizontalMidpoint = position.y + (bounds.y / 2);

    //Position of the box
    Point pos = collider->getPosition();
    //dimensions of the box
    Point dimensions;

    //if the collider is nonstatic, account for velocity
    if (collider->getStatic()) {
        dimensions = Point(collider->getWidth(), collider->getHeight());
    }
    else {
        Point vel = collider->getVelocity();
        dimensions = Point(collider->getWidth() + fabs(vel.x), collider->getHeight() + fabs(vel.y));

        //Account for the direction of the velocity
        if (vel.x < 0.0) {
            pos = pos + Point(vel.x, 0.0);
        }

        if (vel.y < 0.0) {
            pos = pos + Point(0.0, vel.y);
        }

    }

    //Object can completely fit within the top quadrants
    bool topQuadrant = (pos.y < horizontalMidpoint && pos.y + dimensions.y < horizontalMidpoint);
    //Object can completely fit within the bottom quadrants
    bool bottomQuadrant = (pos.y > horizontalMidpoint);

    //Object can completely fit within the left quadrants
    if (pos.x < verticalMidpoint && pos.x + dimensions.x < verticalMidpoint) {
        if (topQuadrant) {
            index = 1;
        }
        else if (bottomQuadrant) {
            index = 2;
        }
    }
    //Object can completely fit within the right quadrands
    else if (pos.x > verticalMidpoint) {
        if (topQuadrant) {
            index = 0;
        }
        else if (bottomQuadrant) {
            index = 3;
        }
    }

    return index;
}
