#include "quadTree.h"
#include <iostream>
#include "System\graphics\global_graphical_variables.h"
#include "GameObject\Component\graphics\renderer.h"

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
}

vector<PolygonCollider*>* QuadTree::retrieve(vector<PolygonCollider*> *returnColliders, PolygonCollider *collider)
{
    int index = getIndex(collider);
    if (index != -1 && nodes[0] != nullptr) {
        nodes[index]->retrieve(returnColliders, collider);
    }
    else if (nodes[0] != nullptr)//If collider does not fit into the node, get all of the children 
    {
        for (int i = 0; i < sizeof(nodes) / sizeof(*nodes); i++) {
            nodes[i]->retrieve(returnColliders, collider);
        }
    }
    //Position of the box
    Point colliderPos = collider->getPosition() + collider->getPolygon().getEffectiveOrigin();
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

    bool overlap = colliderPos.x + colliderDimensions.x >= position.x && colliderPos.x < position.x + bounds.x
         && colliderPos.y + colliderDimensions.y >= position.y && colliderPos.y < position.y + bounds.y;


    if (overlap) {
        returnColliders->reserve(returnColliders->size() + colliders.size());
        returnColliders->insert(returnColliders->end(), colliders.begin(), colliders.end());
    }

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

    colliders.push_back(collider);

    if (colliders.size() > Max_Objects && level < Max_Levels) {
        if (nodes[0] == nullptr) {
            split();
        }
        int i = 0;
        while (i < colliders.size()) {
            int index = getIndex(colliders[i]);
            if (index != -1) {
                nodes[index]->insert(colliders[i]);
                colliders.erase(colliders.begin() + i);
            } else {
                i++;
            }
        }
    }
}

void QuadTree::setBounds(Point _bounds)
{
    bounds = Point(_bounds.x, _bounds.y);
}

void QuadTree::draw()
{
    Point camPos = Renderer::getCameraPosition();
    
    SDL_Rect outlineRect = { position.x - camPos.x, position.y - camPos.y, bounds.x, bounds.y };

    SDL_SetRenderDrawColor(ACTIVE_RENDERER, 0x00, 0x00, 0xFF, 0x00);
    SDL_RenderDrawRect(ACTIVE_RENDERER, &outlineRect);
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
    Point colliderPos = collider->getPosition() + collider->getPolygon().getEffectiveOrigin();
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
    if (colliderPos.x + colliderDimensions.x < verticalMidpoint) {
        if (topQuadrant) {
            index = 1;
        }
        else if (bottomQuadrant) {
            index = 2;
        }
    }
    //Object can completely fit within the right quadrants
    else if (colliderPos.x > verticalMidpoint) {
        if (topQuadrant) {
            index = 0;
        }
        else if (bottomQuadrant) {
            index = 3;
        }
    }

    return index;
}
