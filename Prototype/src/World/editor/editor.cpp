#include "editor.h"
#include "System/IO/inputManager.h"
#include "windows.h"
#include <sstream>
#include <algorithm>
#include "math\rectangle.h"
#include "math\lTimer.h"

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
    //Main loop flag
    bool quit = false;
    //Event handler
    SDL_Event e;
    //The frames per second timer
    LTimer fpsTimer;
    //The frames per second cap timer
    LTimer capTimer;
    //In memory text stream
    std::stringstream timeText;
    //Start counting frames per second
    long countedFrames = 0;
    fpsTimer.start();


    string path = getFilePath();
    if (path.size() > 0) {
        loadFile(path);
        while (!editorWindow->hasExited()) {
            capTimer.start();
            //Calculate and correct fps
            float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
            if (avgFPS > 2000000)
            {
                avgFPS = 0;
            }


            updateInput();

            if (editorWindow->popClickQueue()) {
                if (editorWindow->withinSelector()) {
                    editorWindow->setSelectedTile();
                }
                else {
                    setTile();
                }
            }

            //If frame finished early
            int frameTicks = capTimer.getTicks();
            if (frameTicks < SCREEN_TICK_PER_FRAME) {
                //Wait remaining time
                SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
            }
            countedFrames++;

            LWindow::updateAll();
            //updateInputManager();
        }
        activeRoom->saveToFile();
    }
}

void Editor::setTile()
{
    int x = 0;
    int y = 0;

    Tile *tile;
    editorWindow->getActiveTileCoordinates(x,y);
    if (editorWindow->getSelectedTile() >= TextureManager::TOTAL_TILE_TEXTURES) {
        tile = NULL;
    }
    else {
        tile = new Tile(editorWindow->getSelectedTile(), Rectangular(Point(0.0, 0.0), 32, 32));
    }
    activeRoom->setTile(x, y, tile);
}

void Editor::updateInput()
{
    int dX = 0;
    int dY = 0;

    if (getKeyDown(INPUT_KEY_W)) {
        dY -= 7;
    }
    if (getKeyDown(INPUT_KEY_S)) {
        dY += 7;
    }
    if (getKeyDown(INPUT_KEY_A)) {
        dX -= 7;
    }
    if (getKeyDown(INPUT_KEY_D)) {
        dX += 7;
    }
    editorWindow->updatePosition(dX,dY);
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