#pragma once
#include "GameObject/gameObject.h"
#include <vector>
#include <string>
#include "System/graphics/lTexture.h"
#include "math/point.h"
#include "System/graphics/textureManager.h"
#include "World/Tile.h"

class Room {
public:

    Room(string _file_path);
    ~Room();

    //loads the matrix from .txt file
    //Very important that the grid in the .txt file is rectangular
    void readFromFile();
    //unloads the matrix
    void unload();
    //Saves the room
    void saveToFile();

    //Background texture of this room
    LTexture *background;
    //Gets a point representing the width and height of this room
    Point getDimensions();

    //Get position of room
    Point getPosition();

    //GameObject matrix
    vector<vector<GameObject*>> gameObjectMatrix;
    //Tile info matrix
    vector<vector<Tile*>> tileMatrix;

    //Instantiates room by creating gameObjects
    void instantiate();
    //Removes gameObjects
    void deInstantiate();
private:
    //File path of the room data
    string file_path;

    int tileMapIndex;
    int backgroundIndex;

    //Position of the room in world space
    Point position;
    //Dimensions of this room
    //If room is not loaded these will be negative
    double _width;
    double _height;

    void setFlags(int x, int y);

};