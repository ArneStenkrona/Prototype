#pragma once
#include "GameObject/Component/geometry/polygonCollider.h"
#include "GameObject/gameObject.h"
#include <list>
#include "rayCastHit.h"
#include <string>

class QuadTree;
class PhysicsEngine {
public:
    //All existing hitboxes
    static list<PolygonCollider*> ALL_COLLIDERS;

    static void resetPhysics();
    static void updatePhysics();
    static void performHitdetection();
    //Sets the bounds of the quadTree
    static void setQuadBounds(Point _bounds);

    static void drawQuadTree();

    static void addToMaskLayer(PolygonCollider* col, unsigned int maskLayer);
    static void removeFromMaskLayer(PolygonCollider* col, unsigned int maskLayer);
    static void removeFromAllMaskLayers(PolygonCollider* col);

    //Send ray from a to b
    //Mask layer can be used to ignore colliders, -1 indicates no mask layer
    //Message is sent to collided object
    //Returns true if hit, out can be used for querying hit information
    static bool raycast(Point a, Point b, int maskLayer = -1, std::string message = "");
    static bool raycast(Point a, Point b, RayCastHit* &out, int maskLayer = -1, std::string message = "");

    //Collisions from this frame
    static set<tuple<PolygonCollider*, PolygonCollider*>> currentCollisions;
    //Collisions from previous frame
    static set<tuple<PolygonCollider*, PolygonCollider*>> previousCollisions;

    //QuadTree to reduce unnecessary physics calculations
    //Argument for bounds should be dependent on room size
    static QuadTree quad;

    static vector<set<PolygonCollider*>> mask;
private:
    static void updateQuad();
};