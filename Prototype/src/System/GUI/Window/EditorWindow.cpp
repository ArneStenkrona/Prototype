#include "EditorWindow.h"
#include "System\IO\inputManager.h"
#include <iostream>
#include "System\graphics\global_graphical_variables.h"

const int EditorWindow::gridSize = 32;

EditorWindow::EditorWindow(int _screen_width, int _screen_height, int _scale_x, int _scale_y, Room *_activeRoom): LWindow(_screen_width, _screen_height,
    _scale_x, _scale_y), activeRoom(_activeRoom)
{
}

void EditorWindow::update()
{
    setActiveTileCoordinates();

    //Clear screen
    SDL_SetRenderDrawColor(windowRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(windowRenderer);
    //Render the background
    activeRoom->background->render(0,0);

    //Render the tiles of the room
    renderTiles();
    //X and Y will be passed as referense to get coordinates for the grid and selected grid
    int x = 0;
    int y = 0;
    getDimensions(&x, &y);
    for (int i = 0; i < x / gridSize; i++) {
        for (int j = 0; j < y / gridSize; j++) {
            drawSquare((i * gridSize) - posX, (j * gridSize) - posY, 0x00, 0x00, 0x00, 0x00);
        }
    }
    //Will refactor this for readability. Essentialy I'm translating coordinates so that the grid makes sense
    getMouseCoordinates(&x, &y);
    drawSquare(activeX, activeY, 0xFF,0x00,0x00,0x00);
    SDL_RenderPresent(windowRenderer);
}

void EditorWindow::setRoom(Room * room)
{
    activeRoom = room;
}


void EditorWindow::drawSquare(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_Rect outlineRect = { x, y, gridSize, gridSize };
    SDL_SetRenderDrawColor(windowRenderer, r,g,b,a);
    SDL_RenderDrawRect(windowRenderer, &outlineRect);
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


//This function does not work atm!!!
void EditorWindow::setActiveTileCoordinates()
{
    int x = 0;
    int y = 0;
    getMouseCoordinates(&x, &y);
    activeX = ((((x + (scale_x * (posX % gridSize))) / (gridSize * scale_x)) % gridSize) * gridSize) - (posX % gridSize);
    activeY = ((((y + (scale_y * (posY % gridSize))) / (gridSize * scale_y)) % gridSize) * gridSize) - (posY % gridSize);

}

void EditorWindow::renderTiles()
{
    for (int x = 0; x < activeRoom->tileMatrix.size(); x++) {
        for (int y = 0; y < activeRoom->tileMatrix[x].size(); y++) {
            if (activeRoom->tileMatrix[x][y] != NULL) {
                activeRoom->tileMatrix[x][y]->renderTile((x * gridSize) - posX,(y * gridSize) - posY);
            }
        }
    }
}

void EditorWindow::getActiveTileCoordinates(int & x, int & y)
{
    x = activeX;
    y = activeY;
}

void EditorWindow::updatePosition(int deltaX, int deltaY)
{
    posX += deltaX;
    posY += deltaY;
}
