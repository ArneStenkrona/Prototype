#pragma once
#include "GameObject/Component/geometry/polygonCollider.h"
#include "GameObject/gameObject.h"
#include <list>
#include "rayCastHit.h"
#include <string>

//All existing hitboxes. Probably should not be extern.
extern list<PolygonCollider*> ALL_COLLIDERS;

void updatePhysics();
void performHitdetection();
//Sets the bounds of the quadTree
void setQuadBounds(Point _bounds);

void drawQuadTree();

void addToMaskLayer(PolygonCollider* col, unsigned int maskLayer);
void removeFromMaskLayer(PolygonCollider* col, unsigned int maskLayer);

//Returns true if hit, out can be used for querying hit information
bool raycast(Point a, Point b, int maskLayer = -1, std::string message = "");
bool raycast(Point a, Point b, RayCastHit* &out, int maskLayer = -1, std::string message = "");