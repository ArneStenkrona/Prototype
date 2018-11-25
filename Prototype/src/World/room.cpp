/*
    Right now this file is an awful mess.
    Refactoring should be done.
*/

#include "room.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "System/graphics/textureManager.h"
#include "GameObject/Component/geometry/polygonCollider.h"
#include "math/rectangle.h"
#include "math/triangle.h"
#include "tools/stringTools.h"
#include <algorithm>
#include <optional>

#define toDigit(c) (c-'0')
#define BOOL_STR(b) (b?"T":"F")
#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


Room::Room(const string _file_path, SoundManager::MUSIC _music) 
    : file_path(_file_path), _width(-1), _height(-1), music(_music)
{
    parallaxBackground = new ParallaxBackground(Point::empty);
}

Room::~Room()
{
    unload();
    delete(parallaxBackground);
    parallaxBackground = NULL;
}

void Room::load()
{
    readFromFile();
}

void Room::unload()
{
    deInstantiate();

    for (int x = 0; x < tileMatrix.size(); x++) {
        for (int y = 0; y < tileMatrix[x].size(); y++) {
            delete tileMatrix[x][y];
            tileMatrix[x][y] = nullptr;
        }
    }
    tileMatrix.resize(0);
    _width = -1;
    _height = -1;

}

void Room::saveToFile()
{
    saveToFile(file_path);
}

void Room::saveToFile(const std::string &path)
{
    //opens filestream
    ofstream outFile;

    outFile.open(path);
    //Declares output buffer
    string buffer;

    //Saves info to buffer
    //tilemap
    buffer += std::to_string(tileMapIndex);
    buffer += "\n";
    //background texture
    buffer += std::to_string(backgroundIndex);
    buffer += "\n";
    //world position
    buffer += std::to_string(position.x) + "\n" + std::to_string(position.y) + "\n";


    //tiles
    for (int y = 0; y < tileMatrix[0].size(); y++) {
        for (int x = 0; x < tileMatrix.size(); x++) {

            if (tileMatrix[x][y] != NULL) {
                buffer += "["; // START OF TILE

                buffer += std::to_string(tileMatrix[x][y]->getIndex()) + "| "; //Tile texture index

                buffer += std::to_string(tileMatrix[x][y]->getRotation()) + "| "; //Rotation

                //FLIP
                bool flipH, flipV;
                tileMatrix[x][y]->getFlip(flipH, flipV);
                buffer += BOOL_STR(flipH);
                buffer += BOOL_STR(flipV); 
                buffer += +"| ";


                //Gets all the points of collider if one is present
                if (tileMatrix[x][y]->hasCollider()) {
                    buffer += "<";
                    for (int i = 0; i < tileMatrix[x][y]->getPolygon()->numberOfVertices; i++) {
                        buffer += "(" + std::to_string(tileMatrix[x][y]->getPolygon()->vertices[i].x) + ", ";
                        buffer += std::to_string(tileMatrix[x][y]->getPolygon()->vertices[i].y) + ")";
                    }
                    buffer += ">";
                }
                else {
                    buffer += "N"; //Notifies lack of collider
                }
                buffer += +"| ";

                buffer += std::to_string(tileMatrix[x][y]->getObject());

                buffer += "]"; // END OF TILE
            }
            else {
                buffer += "[N]";
            }

        }
        buffer += "\n";
    }
    outFile << buffer;
    outFile.close();
}

void Room::renderBackground(Point position)
{
    parallaxBackground->renderParallaxLayers(position);
}

Point Room::getDimensions()
{
    return Point(_width, _height);
}

Point Room::getPosition()
{
    return position;
}

void Room::instantiate()
{
    for (int x = 0; x < tileMatrix.size(); x++) {
        for (int y = 0; y < tileMatrix[x].size(); y++) {
            if (tileMatrix[x][y] != NULL) {
                tileGameObjectMatrix[x][y] = tileMatrix[x][y]->gameObjectFromTile(x, y);
                dynamicGameObjectMatrix[x][y] = tileMatrix[x][y]->instantiateObject(x, y);
            }
        }
    }
}

void Room::deInstantiate()
{
    for (int x = 0; x < tileGameObjectMatrix.size(); x++) {
        for (int y = 0; y < tileGameObjectMatrix[x].size(); y++) {
            delete tileGameObjectMatrix[x][y];
            tileGameObjectMatrix[x][y] = nullptr;
            delete dynamicGameObjectMatrix[x][y];
            dynamicGameObjectMatrix[x][y] = nullptr;
        }
    }
    //Shrink vector
    tileGameObjectMatrix.resize(0);
}

Tile * Room::getTile(int x, int y)
{
    if (x >= 0 && x < tileMatrix.size() && y >= 0 && y < tileMatrix[x].size()) {
        return tileMatrix[x][y];
    }
    else {
        std::cout << "Position not defined in tile matrix" << endl;
        std::cout << x << " : " << y << endl;
        return nullptr;
    }
}

void Room::setTile(int x, int y, Tile *tile)
{

    if(x >= 0 && x < tileMatrix.size() && y >= 0 && y < tileMatrix[x].size()) {
        delete(tileMatrix[x][y]);
        tileMatrix[x][y] = tile;
    } else {
        std::cout << "Position not defined in tile matrix" << endl;
        std::cout << x << " : " << y << endl;
    }
}

void Room::getDimensions(int & x, int & y)
{
    x = static_cast<int>(tileMatrix.size());
    y = static_cast<int>(tileMatrix[0].size());
}

void Room::readFromFile()
{
    string roomData;
    ifstream infile;
    infile.open(file_path);
    //reads texture and position data
    if (infile.is_open())
    {
        string line;

        getline(infile, line);
        tileMapIndex = toDigit(line[0]);
        TextureManager::loadTileSet(static_cast<TextureManager::TILEMAPS>(tileMapIndex));

        getline(infile, line);
        backgroundIndex = toDigit(line[0]);
        parallaxBackground->addBackground(&TextureManager::background_layer_textures[(static_cast<TextureManager::BACKGROUND_TEXTURE_NAMES>(backgroundIndex))][0]);
        parallaxBackground->addLayer(&TextureManager::background_layer_textures[(static_cast<TextureManager::BACKGROUND_TEXTURE_NAMES>(backgroundIndex))][1], 1);
        parallaxBackground->addLayer(&TextureManager::background_layer_textures[(static_cast<TextureManager::BACKGROUND_TEXTURE_NAMES>(backgroundIndex))][2], 4);
        parallaxBackground->addLayer(&TextureManager::background_layer_textures[(static_cast<TextureManager::BACKGROUND_TEXTURE_NAMES>(backgroundIndex))][3], 8);

        getline(infile, line);
        double posX = atof(line.c_str());
        getline(infile, line);
        double posY = atof(line.c_str());
        position = Point(posX, posY);
    }

    //Dimensions of the room
    int sizeX = 0;
    int sizeY = 0;

    if (infile.is_open())
    {
        string line;

        while (getline(infile, line))
        {
            roomData += line + '\n';
            sizeY++;
        }
        infile.close();
    }
    //Loop to first linebreak to get x dimension of room
    int index = 0;
    while (roomData[index] != '\n') {
        if (roomData[index] == ']') {
            sizeX++;
        }
        index++;
    }
    //Resize matrix so that it can hold the room
    tileGameObjectMatrix.resize(sizeX);
    dynamicGameObjectMatrix.resize(sizeX);
    tileMatrix.resize(sizeX);
    for (int i = 0; i < sizeX; i++) {
        tileGameObjectMatrix[i].resize(sizeY, NULL);
        dynamicGameObjectMatrix[i].resize(sizeY, NULL);
        tileMatrix[i].resize(sizeY, NULL);
    }
    //Traverses the room and creates tiles
    int x = 0;
    int y = 0;
    //Temporarily tores variables from file
    bool isTile;
    int tileIndex;
    bool hasCollider;
    int rotation;
    bool flipH, flipV;
    int objectIndex;

    std::optional<Polyshape> polygon;
    //buffer to store variable
    vector<string> buffer;

    buffer = brokenStringSplitter(roomData, '\n');
    buffer.pop_back();

    for (int i = 0; i < buffer.size(); i++) {
        //separate by each tile
        vector<string> tileBuffer = brokenStringSplitter(buffer[i], ']');
        tileBuffer.pop_back();
        for (int j = 0; j < tileBuffer.size(); j++) {
            if (tileBuffer[j][0] != 'N') {

                //separate each data point
                vector<string> dataPoints = brokenStringSplitter(tileBuffer[j], '|');

                //Assign variables
                if (dataPoints[0][0] == '[') dataPoints[0].erase(0, 1);
                tileIndex = std::stoi(dataPoints[0]);
                rotation = std::stoi(dataPoints[1]);
                flipH = dataPoints[2][0] != 'F';
                flipV = dataPoints[2][1] != 'F';
                hasCollider = dataPoints[3][0] != 'N';

                if (hasCollider) {
                    polygon = Polyshape::parsePolygon(dataPoints[3]);
                }
                else {
                    polygon = {};
                }

                objectIndex = std::stoi(dataPoints[4]);

                tileMatrix[x][y] = new Tile(tileIndex, rotation,
                    flipH, flipV, polygon, objectIndex);
            }
            x++;
        }
        y++;
        x = 0;
    }

    _width = sizeX * Tile::TILE_SIZE;
    _height = sizeY * Tile::TILE_SIZE;
    parallaxBackground->setOrigin(Point(0, 0));// _width / 2, _height / 2));
}
