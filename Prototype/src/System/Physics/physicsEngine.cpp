#include "physicsEngine.h"
#include "GameObject/gameObject.h"
#include "System/game/gameLogic.h"
#include "data_structures/quadTree.h"
#include "System/graphics/graphicsEngine.h"
#include <vector>
#include <tuple>
#include <iostream>
#include "System\Physics\collision.h"
#include <map>
#include <set>

//All existing hitboxes, both active and inactive
list<PolygonCollider*> ALL_COLLIDERS = list<PolygonCollider*>();
//All active hitboxes
list<PolygonCollider*> activeColliders = list<PolygonCollider*>();

//Collisions from this frame
set<tuple<PolygonCollider*, PolygonCollider*>> currentCollisions = set<tuple<PolygonCollider*, PolygonCollider*>>();
//Collisions from previous frame
set<tuple<PolygonCollider*, PolygonCollider*>> previousCollisions = set<tuple<PolygonCollider*, PolygonCollider*>>();

//QuadTree to reduce unnecessary physics calculations
//Argument for bounds should be dependent on room size
QuadTree quad = QuadTree(0, Point(0, 0), Point(GraphicsEngine::SCREEN_WIDTH * 2, GraphicsEngine::SCREEN_HEIGHT * 2));

//Updates the quad tree with all active hitboxes
void updateQuad() {

    //Clear previous frame
    quad.clear();

    for each (PolygonCollider *b in ALL_COLLIDERS)
    {
        if (b->getActive()) {
            quad.insert(b);
        }
    }
}

void updatePhysics()
{
    updateQuad();
    performHitdetection();
}


void performHitdetection() {

    for each (PolygonCollider *b in ALL_COLLIDERS)
    {
        if (!b->getStatic() && b->getActive()) {
            vector<PolygonCollider*> returnColliders;
            quad.retrieve(&returnColliders, b);

            vector<Collision*> collisions = PolygonCollider::calculateCollision(b, &returnColliders);
            for each (Collision *collision in collisions) {
                
                if (previousCollisions.find(make_tuple(b, collision->getOtherCollider())) == previousCollisions.end()) {
                    b->getGameObject()->onCollisionEnter(collision);
                }
                b->getGameObject()->onColliding(collision);

                currentCollisions.insert(make_tuple(b, collision->getOtherCollider()));
            }
            
        }       
    }
    for each (tuple<PolygonCollider*, PolygonCollider*> colPair in previousCollisions) {
        if (currentCollisions.find(colPair) == currentCollisions.end()) {
            get<0>(colPair)->getGameObject()->onCollisionExit();
        }
    }
    previousCollisions = currentCollisions;
    currentCollisions.clear();
}

void setQuadBounds(Point _bounds)
{
    quad.setBounds(_bounds);
}

void drawQuadTree()
{
    quad.draw();
}


