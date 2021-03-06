#include "TileMap.h"
#include "tools\stringTools.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "graphicsEngine.h"
#include "World\Tile.h"

#define toDigit(c) (c-'0')

using namespace::std;

TileMap::TileMap(): colliderMatrix(vector<vector<optional<Polyshape>>>())
{
    colliderMatrix.resize(Tile::TILES_PER_ROW);
    for (unsigned int i = 0; i < colliderMatrix.size(); i++) {
        colliderMatrix[i].resize(Tile::TILES_PER_COLUMN);
    }
    for (unsigned int i = 0; i < colliderMatrix.size(); i++) {
        for (unsigned int j = 0; j < colliderMatrix[i].size(); j++) {
            colliderMatrix[i][j] = {};
        }
    }
}

TileMap::~TileMap()
{
    texture.free();
    colliderMatrix.clear();
}

void TileMap::loadFromFile(string texturePath, string colliderPath)
{
    texture.loadFromFile(texturePath, GraphicsEngine::getActiveRenderer());

    string roomData;
    ifstream infile;
    infile.open(colliderPath);
    //reads texture and position data
    if (infile.is_open())
    {

        if (infile.is_open())
        {
            string line;

            while (getline(infile, line))
            {
                roomData += line + '\n';
            }
            infile.close();
        }

        //buffer to store variable
        vector<string> buffer;

        buffer = stringSplitter(roomData, '\n');

        for (unsigned int i = 0; i < buffer.size(); i++) {
            vector<string> dataPoints = stringSplitter(buffer[i], '|');
            int col = std::stoi(dataPoints[0]);
            int row = std::stoi(dataPoints[1]);
            Polyshape pol = Polyshape::parsePolygon(dataPoints[2]);
            colliderMatrix[col][row] = pol;
        }
    }
}
