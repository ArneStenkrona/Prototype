#include "TileMap.h"
#include "tools\stringTools.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "math\rectangle.h"
#include "graphicsEngine.h"

#define toDigit(c) (c-'0')

using namespace::std;

TileMap::TileMap(): colliderMatrix(vector<vector<optional<Polyshape>>>())
{
    colliderMatrix.resize(16);
    for (int i = 0; i < colliderMatrix.size(); i++) {
        colliderMatrix[i].resize(16);
    }
    for (int i = 0; i < colliderMatrix.size(); i++) {
        for (int j = 0; j < colliderMatrix[i].size(); j++) {
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
        string line;

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

        for (int i = 0; i < buffer.size(); i++) {
            vector<string> dataPoints = stringSplitter(buffer[i], '|');
            int col = std::stoi(dataPoints[0]);
            int row = std::stoi(dataPoints[1]);
            Polyshape pol = Polyshape::parsePolygon(dataPoints[2]);
            colliderMatrix[col][row] = pol;
        }
    }
}
