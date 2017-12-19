#pragma once
#include "lwindow.h"
#include <vector>
#include "World\room.h"

/*
    This class represents the main viewport in editing mode.
    It is a mess right now, not unlike a lot of my code.
*/

class EditorWindow : public LWindow {
public:
    EditorWindow(int _screen_width, int _screen_height,
        int _scale_x, int _scale_y, Room *_activeRoom);

    void update();

    void setRoom(Room *room);

    void renderTiles();

    void getActiveTileCoordinates(int &x, int &y);

    //updates the position relative to origin
    void updatePosition(int deltaX, int deltaY);

    //Is the mouse within the select tile area?
    bool withinSelector();

    void setSelectedTile();
    int getSelectedTile();

private:
    static const int gridSize;
    void drawOutlineSquare(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void drawSolidSquare(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    //Room in the editor
    Room *activeRoom;
    //The active tile coordinates
    int activeX;
    int activeY;

    //position relative to origin
    int posX;
    int posY;

    //This tileindex will be used when creating tiles in the editor
    //It might be appropriate to move this responsibility to the editor class
    int selectedTile;

    //Updates activeX and activeY
    void setActiveTileCoordinates();

    void renderTileSelector();
};