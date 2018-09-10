#pragma once
#include "GameObject/Component/geometry/polygonCollider.h"
#include "GameObject/gameObject.h"
#include <list>
#include "rayCastHit.h"

//All existing hitboxes. Probably should not be extern.
extern list<PolygonCollider*> ALL_COLLIDERS;

void updatePhysics();
void performHitdetection();
//Sets the bounds of the quadTree
void setQuadBounds(Point _bounds);

void drawQuadTree();

void addToMaskLayer(PolygonCollider* col, unsigned int maskLayer);
void removeFromMaskLayer(PolygonCollider* col, unsigned int maskLayer);

//Returns rayCastHit for line segment defined by ab, null if no hit
RayCastHit* raycast(Point a, Point b, int maskLayer = -1);