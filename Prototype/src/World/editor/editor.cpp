#include "windows.h"
#include "editor.h"
#include "System/IO/inputManager.h"
#include "System\graphics\graphicsEngine.h"
#include "System\sound\soundManager.h"
#include <sstream>
#include <algorithm>
#include "math\lTimer.h"
#include <iostream>

Editor::Editor()
{
    editorWindow = GraphicsEngine::createEditorWindow(this);
    //Initalize input Manager
    initializeInputManager();
    //Initalize texture manager
    TextureManager::initalizeTextureManager();
    SoundManager::initalizeSoundManager();
}

Editor::~Editor()
{
    delete(editorWindow);
}

void Editor::run()
{
    //Main loop flag
    bool quit = false;
    //Event handler
    SDL_Event e;
    //The frames per second timer
    LTimer fpsTimer;
    //The frames per second cap timer
    LTimer capTimer;
    fpsTimer.start();


    FILE_FLAG openFlag = INVALID_FILE;
    while (openFlag == INVALID_FILE) {
        openFlag = openFile();
    } 

    if (openFlag == SUCCESS_FILE) {
        while (!editorWindow->hasExited()) {
            capTimer.start();

            updateInputManager();

            //If frame finished early
            int frameTicks = capTimer.getMicroSeconds();
            if (frameTicks < GraphicsEngine::MICROSECONDS_PER_FRAME) {
                //Wait remaining time
                SDL_Delay((GraphicsEngine::MICROSECONDS_PER_FRAME - frameTicks) / 1000);
            }
            else {
                if (frameTicks > GraphicsEngine::MICROSECONDS_PER_FRAME + 1) {
                    float fps = 1000000 / frameTicks;
                    std::cout << "FPS LOW: " << fps << ". Expected: " << GraphicsEngine::SCREEN_FPS << std::endl;
                }
            }
            LWindow::updateAll();

        }
        if (MessageBoxA(NULL, "Do you wish to save?", "Save", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDYES) {
            saveAs();
        }
    }
}

void Editor::save()
{
    activeRoom->saveToFile();
}

void Editor::saveAs()
{
    activeRoom->saveToFile(getFilePath(false));
}

void Editor::setRoom(Room *room)
{
    if (activeRoom) {
        activeRoom->unload();
        delete(activeRoom);
    }
    activeRoom = room;
    activeRoom->load();
    editorWindow->setRoom(activeRoom);
}

Editor::FILE_FLAG Editor::openFile(bool requireExistingFile)
{
    currentPath = getFilePath(requireExistingFile);
    if (currentPath.length() > 0) {
        return loadFile(currentPath) ? SUCCESS_FILE : INVALID_FILE;
    }
    else
        return NO_FILE;
}

string Editor::getFilePath(bool requireExistingFile)
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
    if (requireExistingFile) ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    ofn.Flags |= OFN_NOCHANGEDIR;

    

    // Display the Open dialog box. 

    if (requireExistingFile) GetOpenFileNameA(&ofn);
    else GetSaveFileNameA(&ofn);

    string path = ofn.lpstrFile;
    std::replace(path.begin(), path.end(), '\\', '/');
    return path;
    
}

bool Editor::loadFile(const std::string& path)
{
    Room *r = new Room(path);
    if (r->load()) {
        activeRoom = r;;
        editorWindow->setRoom(activeRoom);
        return true;
    }
    else {
        delete(r);
        return false;
    }
}
