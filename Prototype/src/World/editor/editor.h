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

    //The selected tile type
    int selectedTileType;

    void setTile();

    void updateInput();

    //Opens a windows api dialog to find a filepath.
    string getFilePath(bool requireExistingPath);
    void loadFile(std::string path);
};