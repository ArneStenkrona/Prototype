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
#include "tools/stringTools.h"
#include <algorithm>
#include <optional>
#include "World\objects\object.h"

#define toDigit(c) (c-'0')
#define BOOL_STR(b) (b?"T":"F")
#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


Room::Room(const string _file_path, SoundManager::MUSIC _music) 
    : file_path(_file_path), _width(-1), _height(-1), music(_music), instantiated(false)
{
    parallaxBackground = new ParallaxBackground(Point::empty);
}

Room::Room(const std::string _file_path, int x, int y, SoundManager::MUSIC _music,
      int _tileMapIndex, int _backgroundIndex)
    : file_path(_file_path), _width(-1), _height(-1), 
      music(_music), tileMapIndex(_tileMapIndex), 
      backgroundIndex(_backgroundIndex), instantiated(false)
{
    parallaxBackground = new ParallaxBackground(Point::empty);

    tileMatrix.resize(x);
    for (int i = 0; i < x; i++) {
        tileMatrix[i].resize(y, NULL);
    }

    saveToFile();
}

Room::~Room()
{
    unload();
    if (parallaxBackground) {
        delete(parallaxBackground);
        parallaxBackground = NULL;
    }
}

bool Room::load()
{
    return readFromFile();
}

void Room::unload()
{
    deinstantiate();

    for (unsigned int x = 0; x < tileMatrix.size(); x++) {
        for (unsigned int y = 0; y < tileMatrix[x].size(); y++) {
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

    if (outFile.is_open()) {

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
        for (unsigned int y = 0; y < tileMatrix[0].size(); y++) {
            for (unsigned int x = 0; x < tileMatrix.size(); x++) {

                if (tileMatrix[x][y] != NULL) {
                    buffer += "["; // START OF TILE

                    buffer += std::to_string(tileMatrix[x][y]->getIndex()) + "|"; //Tile texture index

                    buffer += std::to_string(tileMatrix[x][y]->getRotation()) + "|"; //Rotation

                    //FLIP
                    bool flipH, flipV;
                    tileMatrix[x][y]->getFlip(flipH, flipV);
                    buffer += BOOL_STR(flipH);
                    buffer += BOOL_STR(flipV);
                    buffer += +"|";


                    //Gets all the points of collider if one is present
                    if (tileMatrix[x][y]->hasCollider()) {
                        buffer += "<";
                        for (unsigned int i = 0; i < tileMatrix[x][y]->getPolygon()->numberOfVertices; i++) {
                            buffer += "(" + std::to_string(tileMatrix[x][y]->getPolygon()->vertices[i].x) + ",";
                            buffer += std::to_string(tileMatrix[x][y]->getPolygon()->vertices[i].y) + ")";
                        }
                        buffer += ">";
                    }
                    else {
                        buffer += "N"; //Notifies lack of collider
                    }
                    buffer += +"|";

                    //Object index and possible object parameters
                    int objectIndex = tileMatrix[x][y]->getObject();
                    buffer += std::to_string(objectIndex);
                    if (objectIndex > -1) {
                        for (std::string parameter : tileMatrix[x][y]->getObjectParameters()) {
                            buffer += "," + parameter;
                        }
                    }

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
        outFile.clear();
    }
    else {
        std::cout << "Error: Unable to open: " << file_path << std::endl;
    }
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
    if (!instantiated) {
        for (unsigned int x = 0; x < tileMatrix.size(); x++) {
            for (unsigned int y = 0; y < tileMatrix[x].size(); y++) {
                if (tileMatrix[x][y] != NULL) {
                    //Create Tile
                    tileGameObjects.push_back(tileMatrix[x][y]->gameObjectFromTile(x, y));
                    //Create Object
                    dynamicGameObjects.push_back(tileMatrix[x][y]->instantiateObject(x, y));
                }
            }
        }
    }
    instantiated = true;
}

void Room::deinstantiate()
{
    for (GameObject* g : tileGameObjects) {
        delete g;
    }
    for (GameObject* g : dynamicGameObjects) {
        delete g;
    }
    dynamicGameObjects.clear();
    tileGameObjects.clear();
    instantiated = false;
}

Tile * Room::getTile(int x, int y)
{
    if (x >= 0 && x < (signed)tileMatrix.size() && y >= 0 && y < (signed)tileMatrix[x].size()) {
        return tileMatrix[x][y];
    }
    else {
        std::cout << "Position not defined in tile matrix" << endl;
        std::cout << x << " : " << y << endl;
        return nullptr;
    }
}

Tile * Room::getOrCreateTile(int x, int y)
{
    Tile* t = getTile(x, y);
    //If no tile exists, create one
    if (!t) {
        t = new Tile();
        setTile(x, y, t);
    }
    return t;
}

void Room::setTile(int x, int y, Tile *tile)
{

    if(x >= 0 && x < (signed)tileMatrix.size() && y >= 0 && y < (signed)tileMatrix[x].size()) {
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

bool Room::readFromFile()
{
    string roomData;
    ifstream infile;
    infile.open(file_path);
    try {
        //reads texture and position data
        if (infile.is_open())
        {
            string line;

            getline(infile, line);
            tileMapIndex = toDigit(line[0]);
            TextureManager::loadTileSet(static_cast<TextureManager::TILEMAPS>(tileMapIndex));

            getline(infile, line);
            backgroundIndex = toDigit(line[0]);
            parallaxBackground = new ParallaxBackground(Point::empty);
            parallaxBackground->addBackground(&TextureManager::background_layer_textures[(static_cast<TextureManager::BACKGROUND_TEXTURE_NAMES>(backgroundIndex))][0]);
            parallaxBackground->addLayer(&TextureManager::background_layer_textures[(static_cast<TextureManager::BACKGROUND_TEXTURE_NAMES>(backgroundIndex))][1], 6, true);
            parallaxBackground->addLayer(&TextureManager::background_layer_textures[(static_cast<TextureManager::BACKGROUND_TEXTURE_NAMES>(backgroundIndex))][2], 4, true);

            getline(infile, line);
            double posX = atof(line.c_str());
            getline(infile, line);
            double posY = atof(line.c_str());
            position = Point(posX, posY);

            //Dimensions of the room
            int sizeX = 0;
            int sizeY = 0;

            while (getline(infile, line))
            {
                roomData += line + '\n';
                sizeY++;
            }
            infile.close();

            //Loop to first linebreak to get x dimension of room
            int index = 0;
            while (roomData[index] != '\n') {
                if (roomData[index] == ']') {
                    sizeX++;
                }
                index++;
            }
            //Resize matrix so that it can hold the room
            tileMatrix.resize(sizeX);
            for (int i = 0; i < sizeX; i++) {
                tileMatrix[i].resize(sizeY, NULL);
            }
            _width = sizeX * Tile::TILE_SIZE;
            _height = sizeY * Tile::TILE_SIZE;
            parallaxBackground->setOrigin(Point(0, 0));

            //Traverses the room and creates tiles
            int x = 0;
            int y = 0;

            int tileIndex;
            bool hasCollider;
            int rotation;
            bool flipH, flipV;
            int objectIndex;

            std::optional<Polyshape> polygon;
            //buffer to store variable
            vector<string> buffer;

            buffer = stringSplitter(roomData, '\n');

            for (unsigned int i = 0; i < buffer.size(); i++) {
                //separate by each tile
                vector<string> tileBuffer = stringSplitter(buffer.at(i), ']');
                for (unsigned int j = 0; j < tileBuffer.size(); j++) {
                    if (tileBuffer.at(j).at(1) != 'N') {

                        //separate each data point
                        vector<string> dataPoints = stringSplitter(tileBuffer.at(j), '|');

                        //Assign variables
                        if (dataPoints.at(0).at(0) == '[') dataPoints.at(0).erase(0, 1);
                        tileIndex = std::stoi(dataPoints.at(0));
                        rotation = std::stoi(dataPoints.at(1));
                        flipH = dataPoints.at(2).at(0) != 'F';
                        flipV = dataPoints.at(2).at(1) != 'F';
                        trim(dataPoints.at(3));
                        hasCollider = dataPoints.at(3).at(0) != 'N';

                        if (hasCollider) {
                            polygon = Polyshape::parsePolygon(dataPoints.at(3));
                        }
                        else {
                            polygon = {};
                        }

                        //Object and possible parameters
                        std::vector<std::string> obj = stringSplitter(dataPoints.at(4), ',');
                        objectIndex = std::stoi(obj.at(0));
                        std::vector<std::string> parameters;
                        for (unsigned int k = 1; k < obj.size(); k++) {
                            parameters.push_back(obj.at(k));
                        }

                        tileMatrix[x][y] = new Tile(tileIndex, rotation,
                            flipH, flipV, polygon, objectIndex, parameters);
                    }
                    x++;
                }
                y++;
                x = 0;


            }
            infile.close();
        }
        else {
            std::cout << "Error: Unable to open: " << file_path << std::endl;
            return false;
        }

    }
    catch (const std::out_of_range& oor){
        std::cerr << "Out of Range error: " << oor.what() << '\n';
        return false;
    }
    return true;
}
