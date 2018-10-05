#include "EditorWindow.h"
#include "System\IO\inputManager.h"
#include <iostream>
#include "System\graphics\textureManager.h"
#include "System\GUI\UIElement\UITileSelector.h"
#include "System\graphics\graphicsEngine.h"
#include "System\GUI\UIElement\UIPrompt.h"
#include "System\GUI\UIElement\UIButton.h"
#include "World\editor\editor.h"

const int EditorWindow::gridSize = 32;

EditorWindow::EditorWindow(Editor* _editor, int _screen_width, int _screen_height, int _scale_x, int _scale_y, Room *_activeRoom): LWindow(_screen_width, _screen_height,
    _scale_x, _scale_y), activeRoom(_activeRoom), editor(_editor)
{
    gridSelector = new UIGridSelector(_activeRoom, 0, 0, 2);

    buttons[NEW_FILE_BUTTON] = new UIButton(this, 0, 0, 70, 20, 1, "NEW FILE");
    buttons[SAVE_BUTTON] = new UIButton(this, 70, 0, 30, 20, 1,"SAVE");
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
    gridSelector->setRoom(room);
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

void EditorWindow::notify(UIButton * e)
{
    if (e == buttons[NEW_FILE_BUTTON])
        new UIPrompt(50,50,150,50,0, "FILENAME: ");
    else if (e == buttons[SAVE_BUTTON])
        editor->save();
}