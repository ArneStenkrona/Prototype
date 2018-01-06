#pragma once
#include "GameObject/Component/geometry/polygonCollider.h"
#include "GameObject/gameObject.h"
#include <list>

//All existing hitboxes. Probably should not be extern.
extern list<PolygonCollider*> ALL_HITBOXES;

void updatePhysics();
void performHitdetection();
//Sets the bounds of the quadTree
void setQuadBounds(Point _bounds);

void drawQuadTree();