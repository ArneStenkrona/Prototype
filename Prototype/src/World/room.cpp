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

#define toDigit(c) (c-'0')
#define BOOL_STR(b) (b?"T":"F")
#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


Room::Room(string _file_path) : file_path(_file_path), _width(-1), _height(-1)
{
}

Room::~Room()
{
    unload();
    background = NULL;
}

void Room::readFromFile()
{
    string roomData;
    ifstream infile;
    infile.open(file_path + "test");
    //reads texture and position data
    if (infile.is_open())
    {
        string line;

        getline(infile, line);
        tileMapIndex = toDigit(line[0]);
        TextureManager::loadTileSet(static_cast<TextureManager::TILEMAPS>(tileMapIndex));

        getline(infile, line);
        backgroundIndex = toDigit(line[0]);
        background = &TextureManager::background_textures[(static_cast<TextureManager::BACKGROUND_TEXTURE_NAMES>(backgroundIndex))];

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
    gameObjectMatrix.resize(sizeX);
    tileMatrix.resize(sizeX);
    for (int i = 0; i < sizeX; i++) {
        gameObjectMatrix[i].resize(sizeY, NULL);
        tileMatrix[i].resize(sizeY, NULL);
    }
    //Traverses the room and creates tiles
    int x = 0;
    int y = 0;
    //Temporarily tores variables from file
    bool isTile;
    int tileIndex;
    bool hasCollider;
    Polygon polygon;
    //buffer to store variable
    vector<string> buffer;

    buffer = stringSplitter(roomData, '\n');
    buffer.pop_back();

    for (int i = 0; i < buffer.size(); i++) {
        //separate by each tile
        vector<string> tileBuffer = stringSplitter(buffer[i], ']');
        tileBuffer.pop_back();
        for (int j = 0; j < tileBuffer.size(); j++) {
            if (tileBuffer[j][0] != 'N') {

                //separate each data point
                vector<string> dataPoints = stringSplitter(tileBuffer[j], '|');

                //Assign variables
                isTile = dataPoints[0][1] == 'T';
                tileIndex = std::stoi(dataPoints[1]);
                hasCollider = dataPoints[2][0] == 'T';

                if (hasCollider) {
                    dataPoints[3].erase(0, 1);
                    dataPoints[3].pop_back();
                    //separate by points
                    vector<string> pointStrings = stringSplitter(dataPoints[3], ')');
                    pointStrings.pop_back();

                    vector<Point> points;
                    for (int k = 0; k < pointStrings.size(); k++) {
                        vector<string> doubles = stringSplitter(pointStrings[k], ',');
                        points.push_back(Point(atof(doubles[0].c_str()), atof(doubles[1].c_str())));
                    }

                    if (points.size() == 3) {
                        polygon = Triangle(points[0], points[1], points[2]);

                    }
                    else {
                        polygon = Rectangular(points[0], points[1], points[2], points[3]);
                    }

                }
                else {
                    polygon = Rectangular(Point::empty, 0, 0);
                }
                tileMatrix[x][y] = new Tile;
                tileMatrix[x][y]->isTile = isTile;
                tileMatrix[x][y]->x = x; tileMatrix[x][y]->y = y;
                tileMatrix[x][y]->tileIndex = tileIndex;
                tileMatrix[x][y]->hasCollider = hasCollider;
                tileMatrix[x][y]->polygon = polygon;

                gameObjectMatrix[x][y] = createTile(*tileMatrix[x][y]);
            }
            x++;

        }

        y++;
        x = 0;

    }

    for (int x = 0; x < gameObjectMatrix.size(); x++) {
        for (int y = 0; y < gameObjectMatrix[x].size(); y++) {
            if (gameObjectMatrix[x][y] != NULL) {
                setFlags(x, y);
            }
        }
    }

    _width = sizeX * 32.0;
    _height = sizeY * 32.0;
}

void Room::unload()
{
    for (int x = 0; x < gameObjectMatrix.size(); x++) {
        for (int y = 0; y < gameObjectMatrix[x].size(); y++) {
            delete gameObjectMatrix[x][y];
            gameObjectMatrix[x][y] = nullptr;
            delete tileMatrix[x][y];
            tileMatrix[x][y] = nullptr;
        }
    }
    //Shrink vector
    gameObjectMatrix.resize(0);
    tileMatrix.resize(0);
    _width = -1;
    _height = -1;

}

void Room::saveToFile()
{
    //opens filestream
    ofstream outFile;

    outFile.open(file_path + "test");
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
                buffer += "[";
                buffer += BOOL_STR(tileMatrix[x][y]->isTile); //isTile
                buffer += "| ";

                buffer += std::to_string(tileMatrix[x][y]->tileIndex) + "| "; //Tile texture index

                buffer += BOOL_STR(tileMatrix[x][y]->hasCollider); //is collider present
                buffer += "| ";

                //Gets all the points of collider if one is present
                if (tileMatrix[x][y]->hasCollider) {
                    buffer += "<";
                    for (int i = 0; i < tileMatrix[x][y]->polygon.numberOfVertices; i++) {
                        buffer += "(" + std::to_string(tileMatrix[x][y]->polygon.vertices[i].x) + ", ";
                        buffer += std::to_string(tileMatrix[x][y]->polygon.vertices[i].y) + ")";
                    }
                    buffer += ">";
                }
                else {
                    buffer += "N"; //Notifies lack of collider
                }

                buffer += "]";
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

Point Room::getDimensions()
{
    return Point(_width, _height);
}

Point Room::getPosition()
{
    return position;
}


void Room::setFlags(int x, int y)
{

    bool up = false;
    bool right = false;
    bool left = false;
    bool down = false;

    int indexX = x;
    int indexY = y - 1;

    //Check up
    if (indexX >= 0 && indexX < gameObjectMatrix.size() && indexY >= 0 && indexY < gameObjectMatrix[indexX].size()) {

        if (gameObjectMatrix[indexX][indexY] != NULL) {
            up = true;
        }
    }

    indexX++;
    indexY++;

    //Check right
    if (indexX >= 0 && indexX < gameObjectMatrix.size() && indexY >= 0 && indexY < gameObjectMatrix[indexX].size()) {

        if (gameObjectMatrix[indexX][indexY] != NULL) {
            right = true;
        }
    }

    indexX -= 2;

    //Check left
    if (indexX >= 0 && indexX < gameObjectMatrix.size() && indexY >= 0 && indexY < gameObjectMatrix[indexX].size()) {

        if (gameObjectMatrix[indexX][indexY] != NULL) {
            left = true;
        }
    }
    indexX++;
    indexY++;
    //Check down
    if (indexX >= 0 && indexX < gameObjectMatrix.size() && indexY >= 0 && indexY < gameObjectMatrix[indexX].size()) {

        if (gameObjectMatrix[indexX][indexY] != NULL) {
            down = true;
        }
    }
    gameObjectMatrix[x][y]->getComponent<PolygonCollider>()->setFlags(up, right, left, down);
}


