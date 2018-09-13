#pragma once
#include "UIElement.h"
#include "UIGridTile.h"
#include "World\room.h"
#include "UITileSelector.h"

class EditorWindow;
class UIGridSelector : public UIElement {
public:
    UIGridSelector(Room* _room, int _posx, int _posy, int _layer);

    void setPosition(int x, int y);

    void setRoom(Room* _room);
    void setTile(int x, int y);

private:
    unsigned int columns, rows;
    void render();
    void update();
    void onMouseOver();

    Room* room;
    UITileSelector* tileSelector;
    std::vector<std::vector<UIGridTile*>> tiles;
};