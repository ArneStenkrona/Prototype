#pragma once
#include "lwindow.h"
#include <vector>
#include "World\room.h"
#include "System\GUI\UIElement\UITileSelector.h"
#include "System\GUI\UIElement\UIGridSelector.h"

/*
    This class represents the main viewport in editing mode.
*/
class UIButton;
class Editor;
class EditorWindow : public LWindow {
public:
    EditorWindow(Editor* _editor, int _screen_width, int _screen_height,
        int _scale_x, int _scale_y, Room *_activeRoom);

    void update();

    void setRoom(Room *room);

    //updates the position relative to origin
    void updatePosition(int deltaX, int deltaY);


private:
    Editor *editor;
    //Room in the editor
    Room *activeRoom;
    static const int gridSize;


    //position relative to origin
    int posX;
    int posY;

    static enum BUTTONS {
        NEW_FILE_BUTTON,
        SAVE_BUTTON,
        TOTAL_BUTTONS
    };
    UIButton *buttons[TOTAL_BUTTONS];

    UIGridSelector* gridSelector;

    void drawOutlineSquare(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void drawSolidSquare(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void notify(UIButton* e);
    friend class UIButton;
};