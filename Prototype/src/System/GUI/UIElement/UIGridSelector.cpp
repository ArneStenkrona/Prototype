#include "UIGridSelector.h"
#include "System\graphics\graphicsEngine.h"
#include "System\IO\inputManager.h"
#include <iostream>
#include "System\GUI\Window\EditorWindow.h"
#include "World\Tile.h"

UIGridSelector::UIGridSelector(Room* _room, int _posx, int _posy, int _layer)
    :UIElement(_posx, _posy, 0, 0, _layer + 3, true), room(_room)
{
    setRoom(room);
    tileSelector = new UITileSelector(GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X,
                                      0, _layer, 6, 6);

    colliderSelector = new UIColliderSelector(GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X,
                                                6 * 32, _layer, 6, 2);

    border[0] = new UIBorder(GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X,
                             0, 500, GraphicsEngine::SCREEN_HEIGHT / GraphicsEngine::SCALE_Y + 300, _layer + 1);
    border[1] = new UIBorder(0, GraphicsEngine::SCREEN_HEIGHT / GraphicsEngine::SCALE_Y,
                             GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X + 500, 300, _layer + 1);
}

UIGridSelector::~UIGridSelector()
{
    delete(tileSelector);
    delete(colliderSelector);
    delete(border[0]);
    delete(border[1]);
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
    room->setTile(x, y, tileSelector->getTile());
}