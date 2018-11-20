#pragma once
#include "GameObject/gameObject.h"
#include <vector>
#include <string>
#include "System/graphics/lTexture.h"
#include "math/point.h"
#include "System/graphics/textureManager.h"
#include "World/Tile.h"
#include "System\graphics\parallaxBackground.h"
#include "System\sound\soundManager.h"

class Room {
public:

    Room(const std::string _file_path);
    ~Room();

    //loads the matrix from .txt file
    //Very important that the grid in the .txt file is rectangular
    void load();
    //unloads the matrix
    void unload();
    //Saves the room
    void saveToFile(const std::string &path);
    //Saves the room, with default argument being the file_path variable.
    void saveToFile();



    void renderBackground(Point position);

    //Gets a point representing the width and height of this room
    Point getDimensions();

    //Get position of room
    Point getPosition();

    //Tile GameObject matrix
    vector<vector<GameObject*>> tileGameObjectMatrix;
    //Dynamic GameObject matrix
    vector<vector<GameObject*>> dynamicGameObjectMatrix;

    //Tile info matrix
    vector<vector<Tile*>> tileMatrix;

    //Instantiates room by creating gameObjects
    void instantiate();
    //Removes gameObjects
    void deInstantiate();

    Tile *getTile(int x, int y);
    void setTile(int x, int y, Tile *tile);

    //Sets x and y to the length of the tile vectors
    void getDimensions(int &x, int &y);

private:
    //File path of the room data
    std::string file_path;

    int tileMapIndex;
    int backgroundIndex;

    //Background texture of this room
    //LTexture *background;
    ParallaxBackground *parallaxBackground;

    //Position of the room in world space
    Point position;
    //Dimensions of this room
    //If room is not loaded these will be negative
    double _width;
    double _height;

    //Music to be played in room
    SoundManager::MUSIC music;

    void readFromFile();

};