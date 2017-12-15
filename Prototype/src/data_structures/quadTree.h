#pragma once
#include "../GameObject/gameObject.h"
#include "../GameObject/Component/geometry/polygonCollider.h"
#include <vector>
#include <memory>


//A quadtree splits into 4 nodes each level. This was originally implemented to aid hitBox pair calculations
class QuadTree {

public:
    QuadTree(int pLevel, Point _position, Point _bounds);
    ~QuadTree();

    //Clears all the nodes
    void clear();
    //Splites into for subnodes
    void split();
    //Return all hitboxes that could collide with the given hitbox
    vector<PolygonCollider*> *retrieve(vector<PolygonCollider*> *returnBoxes, PolygonCollider *box);
    /*
    * Insert the object into the quadtree. If the node
    * exceeds the capacity, it will split and add all
    * objects to their corresponding nodes.
    */
    void insert(PolygonCollider *box);
    //Sets the quadtrees bounds
    void setBounds(Point _bounds);

private:
    //Max objects per node level
    int Max_Objects = 10;
    //Max number of levels
    int Max_Levels = 4;

    //int recompile;

    int level;
    vector<PolygonCollider*> hitBoxes;
    //position is the position of this node, bounds are the dimensions
    Point position, bounds;
    QuadTree *nodes[4];

    /*Determine which node the hitBox belongs to.
    *-1 mean object cannot completely fit within a child node
    *and is part of the parent node
    */
    int getIndex(PolygonCollider *box);
};