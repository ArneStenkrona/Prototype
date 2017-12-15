#include "physicsEngine.h"
#include "GameObject/gameObject.h"
#include "System/gameLogic.h"
#include "data_structures/quadTree.h"
#include "System/graphics/global_graphical_variables.h"
#include <vector>
#include <iostream>


//All existing hitboxes, both active and inactive
list<PolygonCollider*> ALL_HITBOXES = list<PolygonCollider*>();
//All active hitboxes
list<PolygonCollider*> activeHitBoxes = list<PolygonCollider*>();

//QuadTree to reduce unnecessary physics calculations
QuadTree quad = QuadTree(0, Point(0, 0), Point(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2));

//Updates the quad tree with all active hitboxes
void updateQuad() {

    //Clear previous frame
    quad.clear();

    for each (PolygonCollider *b in ALL_HITBOXES)
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

    for each (PolygonCollider *b in ALL_HITBOXES)
    {
        if (!b->getStatic() && b->getActive()) {
            vector<PolygonCollider*> returnBoxes;
            quad.retrieve(&returnBoxes, b);


            for each (PolygonCollider *bb in returnBoxes)
            {

                //I should not have to check this
                //Fix quadtree so it doesn't insert b in returnboxes
                if (b != bb) {
                    PolygonCollider::calculateCollision(*b, *bb);
                }
            }

        }

    }
}

void setQuadBounds(Point _bounds)
{
    quad.setBounds(_bounds);
}


