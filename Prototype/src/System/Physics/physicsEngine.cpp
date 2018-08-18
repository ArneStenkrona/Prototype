#include "physicsEngine.h"
#include "GameObject/gameObject.h"
#include "System/game/gameLogic.h"
#include "data_structures/quadTree.h"
#include "System/graphics/global_graphical_variables.h"
#include <vector>
#include <iostream>
#include "System\Physics\collision.h"
#include <map>
#include <set>

//All existing hitboxes, both active and inactive
list<PolygonCollider*> ALL_COLLIDERS = list<PolygonCollider*>();
//All active hitboxes
list<PolygonCollider*> activeColliders = list<PolygonCollider*>();

//QuadTree to reduce unnecessary physics calculations
QuadTree quad = QuadTree(0, Point(0, 0), Point(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2));

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

            vector<PolygonCollider*> possibleCollisions = PolygonCollider::getPossibleCollisions(b, &returnColliders);

            vector<Collision*> collisions;
            for each (PolygonCollider *col in possibleCollisions) {
                Point colNormal;
                double colTime = 1.0;
                if (PolygonCollider::checkCollision(b, col, colNormal, colTime)) {
                    Point relVel = PolygonCollider::getRelativeVelocity(b, col);
                    bool vToV = false;
                    if (relVel.dot(colNormal) < 0.000001) {
                        //Velocity required to reach collision
                        Point velC = b->getVelocity() * colTime;
                        //Is it a vertex to vertex collision?
                        for (int i = 0; i < b->getPolygon().numberOfVertices; i++) {
                            Point aVertex = b->getPolygon().vertices[i] + b->getPosition() + velC;
                            for (int j = 0; j < col->getPolygon().numberOfVertices; j++) {
                                Point bVertex = col->getPolygon().vertices[j] + col->getPosition();
                                if ((aVertex).distanceTo(bVertex) < 0.000001) {
                                    for (int k = 0; k < b->getPolygon().numberOfVertices; k++) {
                                        if (k != i && (col->getPolygon().distanceTo(b->getPolygon().vertices[k] + b->getPosition() + velC - col->getPosition())) >= 0.0001) {
                                            vToV = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (!vToV) {
                        bool onEnter = !Collision::getPreviousCollision(b, col);
                        Collision *collision = new Collision(b, col, colNormal, colTime);
                        if (onEnter) b->getGameObject()->onCollisionEnter(collision);
                        b->getGameObject()->onColliding(collision);
                    }
                }            
            }



            /*if (PolygonCollider::calculateCollision(b, &returnColliders)) {
                //b->getGameObject()->onColliding(nullptr);
            }*/
        }       
    }

    Collision::clearCollisions();
    
}

void setQuadBounds(Point _bounds)
{
    quad.setBounds(_bounds);
}

void drawQuadTree()
{
    quad.draw();
}


