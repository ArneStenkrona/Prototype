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
    //Creates a room object that is loaded from existing file
    Room(const std::string _file_path, SoundManager::MUSIC _music = SoundManager::LAB_MUSIC);

    //Creates a room object and a new room file with dimensions x,y
    Room(const std::string _file_path, int x, int y, SoundManager::MUSIC _music = SoundManager::LAB_MUSIC,
        int _tileMapIndex = 0, int _backgroundIndex = 0);

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
    vector<GameObject*> tileGameObjects;
    //Dynamic GameObject matrix
    vector<GameObject*> dynamicGameObjects;

    //Tile info matrix
    vector<vector<Tile*>> tileMatrix;

    //Instantiates room by creating gameObjects
    void instantiate();
    //Removes gameObjects
    void deinstantiate();

    //Gets tile at position (x, y) in room, may return null
    Tile *getTile(int x, int y);
    //Gets tile at position (x, y) in room. If null, creates and return new tile
    Tile *getOrCreateTile(int x, int y);
    //Sets tile at position (x, y) in room
    void setTile(int x, int y, Tile *tile);

    //Sets x and y to the length of the tile vectors
    void getDimensions(int &x, int &y);

    inline void playMusic() const { SoundManager::playMusic(music); }

private:
    //File path of the room data
    const std::string file_path;

    int tileMapIndex;
    int backgroundIndex;

    //Keeps track of the instantiation status
    bool instantiated;

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

    //Door contained in this room
    //A door number maps to a door in another room denoted by the room path and its door number
    std::map<int, std::tuple<std::string, int>> doors;

};