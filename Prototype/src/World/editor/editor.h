#pragma once
#include "System\GUI\Window\EditorWindow.h"
#include <vector>
#include "World\Tile.h"
#include <string>
#include "World/room.h"

class Editor {
public:
    Editor();
    ~Editor();

    void run();
private:
    EditorWindow *editorWindow;

    vector<vector<Tile*>> *tileMatrix;

    //The room currently being edited;
    Room *activeRoom;

    string getFilePath();
    void loadFile(std::string path);
};