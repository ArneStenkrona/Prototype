#pragma once
#include "../GameObject/gameObject.h"
#include "../GameObject/Component/geometry/polygonCollider.h"
#include <vector>
#include <memory>


//A quadtree splits into 4 nodes each level. The purpose is to optimize collision detection by only
//performing calculations for collisions on nodes covered by the dynamic collider
class QuadTree {

public:
    QuadTree(int pLevel, Point _position, Point _bounds);
    ~QuadTree();

    //Clears all the nodes
    void clear();
    //Splites into for subnodes
    void split();
    //Return all hitboxes that could collide with the given hitbox
    set<PolygonCollider*> *retrieve(set<PolygonCollider*> *returnColliders, PolygonCollider *box);
    //Return all colliders that could collide with the given line ab
    set<PolygonCollider*> *retrieve(set<PolygonCollider*> *returnColliders, Point a, Point b);

    /*
    * Insert the object into the quadtree. If the node
    * exceeds the capacity, it will split and add all
    * objects to their corresponding nodes.
    */
    void insert(PolygonCollider *box);
    //Sets the quadtrees bounds
    void setBounds(Point _bounds);

    void draw();


private:
    //Max objects per node level
    int Max_Objects = 20;
    //Max number of levels
    int Max_Levels = 5;

    //int recompile;

    int level;
    set<PolygonCollider*> colliders;
    //position is the position of this node, bounds are the dimensions
    Point position, bounds;
    QuadTree *nodes[4];

    /*Determine which node the hitBox belongs to.
    *-1 mean object cannot completely fit within a child node
    *and is part of the parent node
    */
    int getIndex(PolygonCollider *box);
};