#pragma once
#include "UIElement.h"
#include "UIGridTile.h"
#include "World\room.h"
#include "UITileSelector.h"
#include "UIColliderSelector.h"
#include "UIBorder.h"

class UIGridSelector : public UIElement {
public:
    UIGridSelector(Room* _room, int _posx, int _posy, int _layer);
    ~UIGridSelector();

    void setPosition(int x, int y);

    void setRoom(Room* _room);
    void setTile(int x, int y);

private:
    unsigned int columns, rows;
    void render();
    void update();
    void onMouseOver();

    void renderRoom();

    Room* room;
    UITileSelector* tileSelector;
    UIColliderSelector* colliderSelector;
    std::vector<std::vector<UIGridTile*>> tiles;

    UIBorder* border[2];
};