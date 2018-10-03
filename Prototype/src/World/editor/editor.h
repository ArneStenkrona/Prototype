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

    std::string currentPath;

    //The room currently being edited;
    Room *activeRoom;

    void updateInput();

    //Asks user for new or pre-existing file
    //returns true if success
    bool openFile();

    //Opens a windows api dialog to find a filepath.
    string getFilePath(bool requireExistingPath);
    void loadFile(const std::string& path);
};