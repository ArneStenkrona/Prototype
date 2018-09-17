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
//list<PolygonCollider*> activeColliders = list<PolygonCollider*>();

//Collisions from this frame
set<tuple<PolygonCollider*, PolygonCollider*>> currentCollisions = set<tuple<PolygonCollider*, PolygonCollider*>>();
//Collisions from previous frame
set<tuple<PolygonCollider*, PolygonCollider*>> previousCollisions = set<tuple<PolygonCollider*, PolygonCollider*>>();

//QuadTree to reduce unnecessary physics calculations
//Argument for bounds should be dependent on room size
QuadTree quad = QuadTree(0, Point(0, 0), Point(GraphicsEngine::SCREEN_WIDTH * 2, GraphicsEngine::SCREEN_HEIGHT * 2));

vector<set<PolygonCollider*>> mask = vector<set<PolygonCollider*>>();

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
            set<PolygonCollider*> returnColliders;
            quad.retrieve(&returnColliders, b);
            //cout << returnColliders.size() << " | " << ALL_COLLIDERS.size() << endl;

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

void addToMaskLayer(PolygonCollider * col, unsigned int maskLayer)
{
    if (maskLayer >= mask.size()) mask.resize(maskLayer + 1);
    mask[maskLayer].insert(col);
}

void removeFromMaskLayer(PolygonCollider * col, unsigned int maskLayer)
{
    if (maskLayer < mask.size())
        mask[maskLayer].erase(col);
}

bool raycast(Point a, Point b, int maskLayer, std::string message)
{
    RayCastHit* out;
    return raycast(a, b, out, maskLayer, message);
}

bool raycast(Point a, Point b, RayCastHit* &out, int maskLayer, std::string message)
{
    RayCastHit* hit;
    set<PolygonCollider*> returnColliders;
    quad.retrieve(&returnColliders, a, b);
    //cout << returnColliders.size() << " | " << ALL_COLLIDERS.size() << endl;

    if (maskLayer >= 0 && maskLayer < mask.size()) {
        for each (PolygonCollider *c in mask[maskLayer]) {
            returnColliders.erase(c);
        }
    }
    vector<RayCastHit*> hits = PolygonCollider::checkRayCast(a, b, returnColliders, message);
    
    if (hits.size() > 0) {
        hits[0]->getOtherCollider()->getGameObject()->rayHit(hits[0]);
        out = hits[0];
        return true;
    }
    return false;
}


