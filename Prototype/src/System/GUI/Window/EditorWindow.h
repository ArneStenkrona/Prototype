#pragma once
#include "lwindow.h"
#include <vector>
#include "World\room.h"
#include "System\GUI\UIElement\UITileSelector.h"
#include "System\GUI\UIElement\UIGridSelector.h"

/*
    This class represents the main viewport in editing mode.
*/
class EditorWindow : public LWindow {
public:
    EditorWindow(int _screen_width, int _screen_height,
        int _scale_x, int _scale_y, Room *_activeRoom);

    void update();

    void setRoom(Room *room);

    //updates the position relative to origin
    void updatePosition(int deltaX, int deltaY);
    //updates position of the tile selector
    void updateTileSelector(int deltaX, int deltaY);
    void setTile(unsigned int x, unsigned int y);

private:
    static const int gridSize;
    void drawOutlineSquare(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void drawSolidSquare(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);


    //Room in the editor
    Room *activeRoom;


    //position relative to origin
    int posX;
    int posY;

    UITileSelector* tileSelector;
    UIGridSelector* gridSelector;
};