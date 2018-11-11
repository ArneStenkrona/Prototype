#include "UIGridSelector.h"
#include "System\graphics\graphicsEngine.h"
#include "System\IO\inputManager.h"
#include <iostream>
#include "System\GUI\Window\EditorWindow.h"
#include "World\Tile.h"
#include "UIButton.h"
#include <optional>

UIGridSelector::UIGridSelector(Room* _room, int _posx, int _posy, int _layer)
    :UIElement(_posx, _posy, GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X,
        GraphicsEngine::SCREEN_HEIGHT / GraphicsEngine::SCALE_Y,
        _layer + 4, true),
    room(_room), infoBox(UIInfoBox(this, 0, GraphicsEngine::SCREEN_HEIGHT / GraphicsEngine::SCALE_Y, 32 * 5, 32 * 3, _layer, "INFO: ")),
    toolSelector(UIToolSelector(GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X + (6 * Tile::TILE_SIZE),
                 0, _layer)),
    objectSelector(UIObjectSelector(GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X,
                  ( 2 * UISelector::LABEL_HEIGHT) + (6 + 2) * Tile::TILE_SIZE, _layer, 6, 2)),
    colliderSelector(UIColliderSelector(GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X,
                     UISelector::LABEL_HEIGHT + 6 * Tile::TILE_SIZE, _layer, 6, 2)),
    tileSelector(UITileSelector(GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X,
                 0, _layer, 6, 6)),
    border{ UIBorder(GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X,
                     0, 500, GraphicsEngine::SCREEN_HEIGHT / GraphicsEngine::SCALE_Y + 300, _layer + 2),
            UIBorder(0, GraphicsEngine::SCREEN_HEIGHT / GraphicsEngine::SCALE_Y,
                     GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X + 500, 300, _layer + 2)}

{
    setRoom(room);
    setSelected(&tileSelector);
    setSelected(this);
}

UIGridSelector::~UIGridSelector()
{
}

void UIGridSelector::render()
{
    renderRoom();
    if (isSelected())
        UIElement::drawSquare(width, height, { 66, 134, 244, 255 }, OUTLINE_SQUARE, ALIGN_CENTER);

}

void UIGridSelector::renderRoom()
{
    room->renderBackground(Point(-roomPosX, -roomPosY));
    for (int x = 0; x < room->tileMatrix.size(); x++) {
        for (int y = 0; y < room->tileMatrix[x].size(); y++) {
            if (room->tileMatrix[x][y] != NULL) {
                room->tileMatrix[x][y]->renderTile((x * Tile::TILE_SIZE) + roomPosX, (y * Tile::TILE_SIZE) + roomPosY);
            }
        }
    }
}

void UIGridSelector::update()
{
    if (!isSelected())
        setActiveTileCoordinates(-1, -1);

    if (isSelected()) {
        int dX = 0;
        int dY = 0;

        if (getKey(INPUT_KEY_W)) {
            dY += 7;
        }
        if (getKey(INPUT_KEY_S)) {
            dY -= 7;
        }
        if (getKey(INPUT_KEY_A)) {
            dX += 7;
        }
        if (getKey(INPUT_KEY_D)) {
            dX -= 7;
        }
        roomPosX += dX;
        roomPosY += dY;
    }
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            tiles[i][j]->updatePosition();

        }
    }

}

void UIGridSelector::onMouseOver()
{
    setActiveTileCoordinates(-1, -1);
}

void UIGridSelector::setRoom(Room* _room)
{
    if (!_room) return;
    room = _room;
    int x = 0;
    int y = 0;
    room->getDimensions(x, y);
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

void UIGridSelector::getActiveTileCoordinates(int & x, int & y)
{
    x = tilePosX;
    y = tilePosY;
}

void UIGridSelector::setElement(int x, int y)
{
    UISelector* s = UISelector::getActiveSelector();

    //*NOTE* Tools should be defined by enum for clariy
    switch (toolSelector.getSelectedIndex()) {
    case UIToolSelector::PLACE_TOOL:
        if (s == &tileSelector)
            room->setTile(x, y, tileSelector.getTile());

        if (s == &colliderSelector) {
            Tile* t = room->getTile(x, y);
            std::optional<Polyshape> p = colliderSelector.getPolygon();
            if (t)
                t->setPolygon(p);
            else {
                t = new Tile();
                t->setPolygon(p);
                room->setTile(x, y, t);
            }
        }
        if (s == &objectSelector) {
            Tile* t = room->getTile(x, y);
            if (t)
                t->setObject(objectSelector.getSelectedIndex());
            else {
                t = new Tile();
                t->setObject(objectSelector.getSelectedIndex());
                room->setTile(x, y, t);
            }
        }
        break;
    case UIToolSelector::DELETE_TOOL:
        room->setTile(x, y, NULL);

        break;
    }
}

void UIGridSelector::setActiveTileCoordinates(int x, int y)
{
    tilePosX = x;
    tilePosY = y;
}
