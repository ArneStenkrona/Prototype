#pragma once
#include "lwindow.h"
#include <vector>
#include "World\room.h"
#include "System\GUI\UIElement\UISelect\UISelector\UITileSelector.h"
#include "System\GUI\UIElement\UIGridEditor.h"
#include "System\GUI\UIElement\UIPanel\UIComponent\UIButton.h"

/*
    This class represents the main viewport in editing mode.
*/
class Editor;
class EditorWindow : public LWindow {
public:
    EditorWindow(Editor* _editor, int _screen_width, int _screen_height,
        float _scale_x, float _scale_y, Room *_activeRoom);

    void update();

    void setRoom(Room *room);

private:
    Editor *editor;
    //Room in the editor
    Room *activeRoom;

    enum BUTTONS {
        NEW_FILE_BUTTON,
        OPEN_FILE_BUTTON,
        SAVE_BUTTON,
        SAVE_AS_BUTTON,
        TOTAL_BUTTONS
    };
    UIButton buttons[TOTAL_BUTTONS];

    UIGridEditor gridEditor;
};