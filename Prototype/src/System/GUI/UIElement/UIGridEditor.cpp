#include "UIGridEditor.h"
#include "System\graphics\graphicsEngine.h"
#include "System\IO\inputManager.h"
#include <iostream>
#include "System\GUI\Window\EditorWindow.h"
#include "World\Tile.h"
#include "UIPanel\UIComponent\UIButton.h"
#include <optional>
#include "System\GUI\UIElement\UIPanel\UIPanel\UIMultiPrompt.h"

class UIObjectPlacementListener : public UIMultiPromptListener {
public:
    UIObjectPlacementListener(Room *_room)
        : UIMultiPromptListener("OBJECT PARAMETERS: ", {}), objectIndex(-1), 
          room(_room), x(-1), y(-1)
    {}

    void ok() {
        UIMultiPromptListener::ok();
        if (objectIndex != -1) {
            room->getOrCreateTile(x, y)->setObject(objectIndex, input);
        }
    }

    void onNotify() {
        if (prompt && !prompt->isSelected()) {
            cancel();
            objectIndex = -1;
            x = -1;
            y = -1;
        }
    }

    void setPlacement(std::vector<std::string> _parameters, int index, int _x, int _y) {
        label = Object::objects[index].name + " PARAMETERS: ";
        labels = _parameters;
        objectIndex = index;
        x = _x;
        y = _y;
    }

    void setRoom(Room *_room) {
        objectIndex = -1;
        x = -1;
        y = -1;
        room = _room;
    }

private:
    int objectIndex;
    //Coordinates of object placement
    int x, y;
    Room *room;
};

UIGridEditor::UIGridEditor(Room* _room, int _posx, int _posy, int _layer)
    :UIElement(_posx, _posy, (int)(GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X),
        (int)(GraphicsEngine::SCREEN_HEIGHT / GraphicsEngine::SCALE_Y),
        _layer + 4, true),
    room(_room), infoBox(UIInfoBox(this, 0, (int)(GraphicsEngine::SCREEN_HEIGHT / GraphicsEngine::SCALE_Y), 32 * 5, 32 * 3, _layer, "INFO: ")),
    toolSelector(UIToolSelector((int)(GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X) + (6 * Tile::TILE_SIZE),
                 0, _layer)),

    objectSelector(UIObjectSelector((int)(GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X),
                  ( 2 * UISelector::LABEL_HEIGHT) + (6 + 4) * Tile::TILE_SIZE, _layer, 6, 5)),

    colliderSelector(UIColliderSelector((int)(GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X),
                     UISelector::LABEL_HEIGHT + 6 * Tile::TILE_SIZE, _layer, 6, 4)),

    tileSelector(UITileSelector((int)(GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X),
                 0, _layer, 6, 6)),

    border{ UIBorder((int)(GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X),
                     0, 500, (int)(GraphicsEngine::SCREEN_HEIGHT / GraphicsEngine::SCALE_Y), _layer + 2, COLOR_DARK_GREY),
            UIBorder(0, (int)(GraphicsEngine::SCREEN_HEIGHT / GraphicsEngine::SCALE_Y),
                     (int)(GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X) + 500, 300, _layer + 2)},

    objectPlacementListener(new UIObjectPlacementListener(room))
{
    setRoom(room);
    setSelected(&tileSelector);
    setSelected(this);
}



UIGridEditor::~UIGridEditor()
{
}

void UIGridEditor::render()
{
    renderRoom();
    if (isSelected())
        UIElement::drawSquare(width, height, { 66, 134, 244, 255 }, OUTLINE, ALIGN_CENTER);

}

void UIGridEditor::renderRoom()
{
    room->renderBackground(Point(-roomPosX, -roomPosY));
    for (unsigned int x = 0; x < room->tileMatrix.size(); x++) {
        for (unsigned int y = 0; y < room->tileMatrix[x].size(); y++) {
            if (room->tileMatrix[x][y] != NULL) {
                room->tileMatrix[x][y]->renderTile((x * Tile::TILE_SIZE) + roomPosX, (y * Tile::TILE_SIZE) + roomPosY);
            }
        }
    }
}

void UIGridEditor::update()
{

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
    for (unsigned int i = 0; i < columns; i++) {
        for (unsigned int j = 0; j < rows; j++) {
            tiles[i][j]->updatePosition();

        }
    }

}

void UIGridEditor::setRoom(Room* _room)
{
    for (unsigned int i = 0; i < columns; i++) {
        for (unsigned int j = 0; j < rows; j++) {
            delete(tiles[i][j]);
            tiles[i][j] = NULL;
        }
    }

    if (!_room) return;
    room = _room;
    int x = 0;
    int y = 0;
    room->getDimensions(x, y);
    columns = x;
    rows = y;

    tiles.resize(columns + 1);
    for (unsigned int i = 0; i < columns; i++) {
        tiles[i].resize(rows);
        for (unsigned int j = 0; j < rows; j++) {
            tiles[i][j] = new UIGridTile(this, layer - 1, i, j);
        }
    }
    roomPosX = 0;
    roomPosY = 0;

    objectPlacementListener->setRoom(room);
}

void UIGridEditor::getActiveTileCoordinates(int & x, int & y)
{
    x = tilePosX;
    y = tilePosY;
}

void UIGridEditor::setTile(int x, int y)
{
    switch (toolSelector.getSelectedIndex()) {
    case UIToolSelector::PLACE_TOOL:
        {
            std::vector<std::vector<Tile*>> selectedTiles = tileSelector.getTiles();
            for (unsigned int i = 0; i < selectedTiles.size(); i++) {
                for (unsigned  int j = 0; j < selectedTiles[i].size(); j++) {
                    room->setTile(x + i, y + j, selectedTiles[i][j]);
                }
            }
            break;
        }
    case UIToolSelector::DELETE_TOOL: 
        {
            room->setTile(x, y, NULL);
            break;
        }
    }
}

void UIGridEditor::setCollider(int x, int y)
{
    switch (toolSelector.getSelectedIndex()) {
    case UIToolSelector::PLACE_TOOL:
        {
            std::optional<Polyshape> p = colliderSelector.getPolygon();
            room->getOrCreateTile(x, y)->setPolygon(p);
            break;
        }
    case UIToolSelector::DELETE_TOOL:
        {
            room->setTile(x, y, NULL);
            break;
        }
    }
}

void UIGridEditor::setObject(int x, int y)
{
    switch (toolSelector.getSelectedIndex()) {
    case UIToolSelector::PLACE_TOOL:
    {
        //Prompt users for parameters
        int index = objectSelector.getSelectedIndex();
        std::vector<std::string> params = Object::objects[index].getParameterNames();
        if (!params.empty()) {
            objectPlacementListener->setPlacement(params, index, x, y);
            objectPlacementListener->actionPerformed(NULL);
        }
        else {
            room->getOrCreateTile(x, y)->setObject(objectSelector.getSelectedIndex());
        }
        break;
    }
    case UIToolSelector::DELETE_TOOL:
        {
            room->setTile(x, y, NULL);
            break;
        }
    }
}

void UIGridEditor::setActiveTileCoordinates(int x, int y)
{
    tilePosX = x;
    tilePosY = y;
}
