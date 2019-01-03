#include "EditorWindow.h"
#include "System\IO\inputManager.h"
#include <iostream>
#include "System\graphics\textureManager.h"
#include "System\GUI\UIElement\UITileSelector.h"
#include "System\graphics\graphicsEngine.h"
#include "System\GUI\UIElement\UIPrompt.h"
#include "System\GUI\UIElement\UIActionListener.h"
#include "World\editor\editor.h"
#include "tools\fileTools.h"
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

const int EditorWindow::gridSize = 32;

class UISaveFileAsListener : public UIActionListener {
public:
    UISaveFileAsListener(Editor* _editor)
    : editor(_editor)
    {}

    void actionPerformed(UIEvent* e) {
        editor->saveAs();
    }
private:
    Editor* editor;
};

class UISaveFileListener : public UIActionListener {
public:
    UISaveFileListener(Editor* _editor)
        : editor(_editor)
    {}

    void actionPerformed(UIEvent* e) {
        editor->save();
    }
private:
    Editor* editor;
};

class UINewFilePromptListener : public UIPromptListener {
public:
    UINewFilePromptListener(Editor* _editor)
        : UIPromptListener("FILENAME: "), editor(_editor)
    {}


    void ok() {
        UIPromptListener::ok();

        bool b = true;

        if (fileExists("Assets/Rooms/" + input + ".room")) {
            if (!(MessageBoxA(NULL, 
                (input + ".room" + " already exists. \n Do you wish to overwrite the existing file?").c_str(),
                "Confirm Overwrite", 
                MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDYES)) {
                b = false;
            }
        }
        if (b) {
            Room* room = new Room("Assets/Rooms/" + input + ".room", 64, 64);
            editor->setRoom(room);
        }
    }
  
private:
    Editor* editor;
};

class UIOpenFileListener : public UIActionListener {
public:
    UIOpenFileListener(Editor* _editor)
        : editor(_editor)
    {}

    void actionPerformed(UIEvent* e) {
        editor->openFile();
    }
private:
    Editor* editor;
};

EditorWindow::EditorWindow(Editor* _editor, int _screen_width, int _screen_height, int _scale_x, int _scale_y, Room *_activeRoom): LWindow(_screen_width, _screen_height,
    _scale_x, _scale_y), activeRoom(_activeRoom), editor(_editor), gridSelector(UIGridSelector(_activeRoom, 0, 0, 2)),
    buttons{ UIButton(new UINewFilePromptListener(editor), 0, 0, 70, 20, 1, "NEW FILE") ,
             UIButton(new UIOpenFileListener(editor), 70, 0, 70, 20, 1, "OPEN FILE"),
             UIButton(new UISaveFileListener(editor), 70 + 70, 0, 40, 20, 1, "SAVE"),
             UIButton(new UISaveFileAsListener(editor), 70 + 70 + 40, 0, 50, 20, 1,"SAVE AS")}
{
}

void EditorWindow::update()
{
    UIElement::updateUIElements();
    LWindow::update();

    //Clear screen
    clear();
    UIElement::renderUIElements();
    present();
}

void EditorWindow::setRoom(Room * room)
{
    activeRoom = room;
    gridSelector.setRoom(room);
}


void EditorWindow::drawOutlineSquare(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_Rect outlineRect = { x, y, gridSize, gridSize };
    SDL_SetRenderDrawColor(mRenderer, r,g,b,a);
    SDL_RenderDrawRect(mRenderer, &outlineRect);
}

void EditorWindow::drawSolidSquare(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_Rect fillRect = { x, y, gridSize, gridSize };
    SDL_SetRenderDrawColor(mRenderer, r, g, b, a);
    SDL_RenderFillRect(mRenderer, &fillRect);
}

