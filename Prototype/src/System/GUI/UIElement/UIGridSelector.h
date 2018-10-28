#pragma once
#include "UIElement.h"
#include "UIGridTile.h"
#include "World\room.h"
#include "UITileSelector.h"
#include "UIColliderSelector.h"
#include "UIObjectSelector.h"
#include "UIToolSelector.h"
#include "UIBorder.h"
#include "UIInfoBox.h"

//Bad name for class, should be something like "UIEditor"
//because of big responsibility and also because it doesn't inherit from UISelector
class UIGridSelector : public UIElement {
public:
    UIGridSelector(Room* _room, int _posx, int _posy, int _layer);
    ~UIGridSelector();

    void setRoom(Room* _room);

    //Checks if gridselector is selected
    inline bool isSelected() const { return selected || UIElement::isSelected(); }

    void getActiveTileCoordinates(int &x, int &y);

private:
    Room* room;
    UITileSelector tileSelector;
    UIColliderSelector colliderSelector;
    UIObjectSelector objectSelector;
    UIToolSelector toolSelector;

    UIInfoBox infoBox;

    std::vector<std::vector<UIGridTile*>> tiles;

    //Is any tile in tiles selected?
    bool selected;
    //room offset position
    int roomPosX, roomPosY;
    //Tells what coordinate tile is active
    int tilePosX, tilePosY;

    UIBorder border[2];
    //Dimensions of the room
    unsigned int columns, rows;
    void render();
    void update();
    void onMouseOver();

    void renderRoom();
    //Sets element from active selector at position (x, y)
    void setElement(int x, int y);
    
    void setActiveTileCoordinates(int x, int y);

    friend class UIGridTile;
};