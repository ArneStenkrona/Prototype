#include "editor.h"
#include "System/IO/inputManager.h"
#include "windows.h"
#include <sstream>
#include <algorithm>

Editor::Editor()
{
    editorWindow = new EditorWindow(2*512,2*288,2,2, NULL);
    //Initalize input Manager
    initializeInputManager();
    //Initalize texture manager
    TextureManager::initalizeTextureManager();
}

Editor::~Editor()
{
    delete(editorWindow);
}

void Editor::run()
{
    string path = getFilePath();
    if (path.size() > 0) {
        loadFile(path);
        while (!editorWindow->hasExited()) {
            LWindow::updateAll();
            //updateInputManager();
        }
        activeRoom->saveToFile();
    }
}

string Editor::getFilePath()
{
    OPENFILENAMEA ofn;       // common dialog box structure
    char szFile[260];       // buffer for file name

                            // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
    // use the contents of szFile to initialize itself.
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box. 

    GetOpenFileNameA(&ofn);

    string path = ofn.lpstrFile;
    std::replace(path.begin(), path.end(), '\\', '/');
    return path;
    
}

void Editor::loadFile(std::string path)
{
    activeRoom = new Room(path);
    activeRoom->readFromFile();
    editorWindow->setRoom(activeRoom);
}
