#pragma once
#include "UIElement.h"
#include "UIGridTile.h"
#include "World\room.h"
#include "UISelect\UISelector\UITileSelector.h"
#include "UISelect\UISelector\UIColliderSelector.h"
#include "UISelect\UISelector\UIObjectSelector.h"
#include "UISelect\UISelector\UIToolSelector.h"
#include "UIBorder.h"
#include "UIPanel\UIPanel\UIInfoBox.h"

class UIObjectPlacementListener;
//Bad name for class, should be something like "UIEditor"
//because of big responsibility and also because it doesn't inherit from UISelector
class UIGridSelector : public UIElement {
public:
    UIGridSelector(Room* _room, int _posx, int _posy, int _layer);
    ~UIGridSelector();

    //Set room to _room. If null is provided, no room is set
    void setRoom(Room* _room);

    //Checks if gridselector is selected
    inline bool isSelected() const { return selected || UIElement::isSelected(); }
    //Gets coordniates of the tile that mouse is currently over.
    //Coordinates may be set to (-1, -1) if not applicable 
    void getActiveTileCoordinates(int &x, int &y);

    inline UIToolSelector::TOOL getTool() const { return (UIToolSelector::TOOL)toolSelector.getSelectedIndex(); }

private:
    Room* room;
    UITileSelector tileSelector;
    UIColliderSelector colliderSelector;
    UIObjectSelector objectSelector;
    UIToolSelector toolSelector;

    UIObjectPlacementListener* objectPlacementListener;

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

    void renderRoom();
    
    //Sets selected tile at position (x, y)
    void setTile(int x, int y);
    //Sets selected collider at position (x, y)
    void setCollider(int x, int y);
    //Sets selected object at position (x, y)
    void setObject(int x, int y);

    void setActiveTileCoordinates(int x, int y);

    friend class UIGridTile;
};