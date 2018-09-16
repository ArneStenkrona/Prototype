#include "UIGridSelector.h"
#include "System\graphics\graphicsEngine.h"
#include "System\IO\inputManager.h"
#include <iostream>
#include "System\GUI\Window\EditorWindow.h"
#include "World\Tile.h"

UIGridSelector::UIGridSelector(Room* _room, int _posx, int _posy, int _layer)
    :UIElement(_posx, _posy, 0, 0, _layer + 2, true), room(_room)
{
    setRoom(room);
    tileSelector = tileSelector = new UITileSelector(0, 0, _layer, 4, 4);
}

void UIGridSelector::setPosition(int x, int y)
{
    positionX = x;
    positionY = y;
}

void UIGridSelector::render()
{
    renderRoom();
}

void UIGridSelector::renderRoom()
{
    for (int x = 0; x < room->tileMatrix.size(); x++) {
        for (int y = 0; y < room->tileMatrix[x].size(); y++) {
            if (room->tileMatrix[x][y] != NULL) {
                room->tileMatrix[x][y]->renderTile((x * 32) + positionX, (y * 32) + positionY);
            }
        }
    }
}

void UIGridSelector::update()
{
}

void UIGridSelector::onMouseOver()
{
}

void UIGridSelector::setRoom(Room* _room)
{
    if (!_room) return;
    room = _room;
    int x = 0;
    int y = 0;
    room->getDimensions(x, y);
    width = x * 32;
    height = y * 32;
    columns = x;
    rows = y;

    tiles.resize(columns + 1);
    for (int i = 0; i < columns; i++) {
        tiles[i].resize(rows);
        for (int j = 0; j < rows; j++) {
            tiles[i][j] = new UIGridTile(this, layer - 1, i, j);
        }
    }
}

void UIGridSelector::setTile(int x, int y)
{
    Tile *tile;
    int selectedTile = tileSelector->getSelectedIndex();
    bool flipH, flipV;
    tileSelector->getFlip(flipH, flipV);
    if (selectedTile == -1) {
        tile = NULL;
    }
    else {
        tile = new Tile(selectedTile, tileSelector->getRotation(),
                        flipH, flipV);
    }
    room->setTile(x, y, tile);
}