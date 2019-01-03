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

    //Asks user for pre-existing file
    //returns true if success
    bool openFile(bool requireExistingFile = true);

    //Saves active room to rooms current file path
    void save();
    //Saves active room to file path specified by the user
    void saveAs();
    
    void setRoom(Room *room);
private:
    EditorWindow *editorWindow;

    std::string currentPath;

    //The room currently being edited;
    Room *activeRoom;

    //Opens a windows api dialog to find a filepath.
    string getFilePath(bool requireExistingPath);
    void loadFile(const std::string& path);
};