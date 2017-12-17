#include "EditorWindow.h"
#include "System\IO\inputManager.h"
#include <iostream>
#include "System\graphics\global_graphical_variables.h"

const int EditorWindow::gridSize = 32;

EditorWindow::EditorWindow(int _screen_width, int _screen_height, int _scale_x, int _scale_y): LWindow(_screen_width, _screen_height,
    _scale_x, _scale_y)
{
}

void EditorWindow::update()
{

    updateInput();

    //Clear screen
    SDL_SetRenderDrawColor(windowRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(windowRenderer);
    int x = 0;
    int y = 0;
    getDimensions(&x, &y);
    for (int i = 0; i < x / gridSize; i++) {
        for (int j = 0; j < y / gridSize; j++) {
            drawSquare(snapToGrid(i * gridSize) - posX, snapToGrid(j * gridSize) - posY, 0x00, 0x00, 0x00, 0x00);
        }
    }
    //Will refactor this for readability. Essentialy I'm translating coordinates so that the grid makes sense
    getMouseCoordinates(&x, &y);
    drawSquare(snapToGrid(x + (scale_x * (posX % gridSize))) - (posX % gridSize), snapToGrid(y + (scale_y * (posY % gridSize))) - (posY % gridSize), 0xFF,0x00,0x00,0x00);
    SDL_RenderPresent(windowRenderer);
}


void EditorWindow::drawSquare(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_Rect outlineRect = { x, y, gridSize, gridSize };
    SDL_SetRenderDrawColor(windowRenderer, r,g,b,a);
    SDL_RenderDrawRect(windowRenderer, &outlineRect);
}

void EditorWindow::updateInput()
{
    if (getKeyDown(INPUT_KEY_W)) {
        posY -= 1;
    }
    if (getKeyDown(INPUT_KEY_S)) {
        posY += 1;
    }
    if (getKeyDown(INPUT_KEY_A)) {
        posX -= 1;
    }
    if (getKeyDown(INPUT_KEY_D)) {
        posX += 1;
    }
}

//This function assumes that scale_x = scale_y
int EditorWindow::snapToGrid(int i)
{
    return ((i / (gridSize * scale_x)) % gridSize) * gridSize;
}

void EditorWindow::getClosestVertex(int &x, int &y)
{
    //TODO: 
}
