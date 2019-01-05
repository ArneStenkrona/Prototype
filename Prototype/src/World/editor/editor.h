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
    //Returns NO_FILE if no file was specified (User canceled)
    //Returns INVALID_FILE if file was invalid
    //Returns SUCCESS_FILE if success
    enum FILE_FLAG {
        NO_FILE = 0,
        INVALID_FILE = 1,
        SUCCESS_FILE = 2,
    };

    FILE_FLAG openFile(bool requireExistingFile = true);

    //Saves active room to rooms current file path
    void save();
    //Saves active room to file path specified by the user
    void saveAs();
    //Sets active room to room.
    void setRoom(Room *room);
private:
    EditorWindow *editorWindow;

    std::string currentPath;

    //The room currently being edited;
    Room *activeRoom;

    //Opens a windows api dialog to find a filepath.
    string getFilePath(bool requireExistingPath);
    //Attempt to load file at path
    //Returns true if success
    bool loadFile(const std::string& path);


};