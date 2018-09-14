#include "EditorWindow.h"
#include "System\IO\inputManager.h"
#include <iostream>
#include "System\graphics\textureManager.h"
#include "System\GUI\UIElement\UITileSelector.h"

const int EditorWindow::gridSize = 32;

EditorWindow::EditorWindow(int _screen_width, int _screen_height, int _scale_x, int _scale_y, Room *_activeRoom): LWindow(_screen_width, _screen_height,
    _scale_x, _scale_y), activeRoom(_activeRoom)
{
    gridSelector = new UIGridSelector(_activeRoom, 0, 0, 0);
}

void EditorWindow::update()
{
    LWindow::update();

    //Clear screen
    clear();
    //Render the background
    activeRoom->renderBackground(Point(posX,posY));

    gridSelector->setPosition(-posX, -posY);
    UIElement::updateUIElements();
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

void EditorWindow::updateTileSelector(int deltaX, int deltaY)
{
    if (deltaX || deltaY) tileSelector->moveIndices(deltaX, deltaY);
}

void EditorWindow::updatePosition(int deltaX, int deltaY)
{
    posX += deltaX;
    posY += deltaY;
}


void EditorWindow::setTile(unsigned int x, unsigned int y)
{
    Tile *tile;
    int selectedTile = tileSelector->getSelectedIndex();
    if (selectedTile == -1) {
        tile = NULL;
    }
    else {
        tile = new Tile(selectedTile);
    }
    activeRoom->setTile(x, y, tile);
}