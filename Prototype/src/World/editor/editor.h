#pragma once
#include "System\GUI\Window\EditorWindow.h"
#include <vector>
#include "World\Tile.h"
#include <string>
#include "World/room.h"
#include "math\polygon.h"

class Editor {
public:
    Editor();
    ~Editor();

    void run();
private:
    EditorWindow *editorWindow;

    vector<vector<Tile*>> *tileMatrix; //Never used?

    //The room currently being edited;
    Room *activeRoom;

    //The selected tile type
    unsigned int tileIndex;

    void setTile();

    void updateInput();

    //Opens a windows api dialog to find a filepath.
    string getFilePath(bool requireExistingPath);
    void loadFile(std::string path);
};