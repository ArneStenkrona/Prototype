#include "EditorWindow.h"
#include "System\IO\inputManager.h"
#include <iostream>
#include "System\graphics\global_graphical_variables.h"
#include "System\graphics\textureManager.h"

const int EditorWindow::gridSize = 32;

EditorWindow::EditorWindow(int _screen_width, int _screen_height, int _scale_x, int _scale_y, Room *_activeRoom): LWindow(_screen_width, _screen_height,
    _scale_x, _scale_y), activeRoom(_activeRoom), selectedTile(0)
{
}

void EditorWindow::update()
{
    LWindow::update();

    setActiveTileCoordinates();

    //Clear screen
    SDL_SetRenderDrawColor(windowRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(windowRenderer);
    //Render the background
    activeRoom->background->render(0,0);

    //Render the tiles of the room
    renderTiles();
    //Render grid, could be optimized by drawing lines instead of squares
    //X and Y will be passed as referense to get coordinates for the grid and selected grid
    int x = 0;
    int y = 0;
    activeRoom->getDimensions(x,y);
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y ; j++) {
            drawOutlineSquare((i * gridSize) - posX, (j * gridSize) - posY, 0x00, 0x00, 0x00, 0x00);
        }
    }

    //Render active square
    if (withinSelector()) {
        renderTileSelector();
        getMouseCoordinates(&x, &y);
        drawOutlineSquare((x / (gridSize * scale_x)) * gridSize, (y / (gridSize * scale_y)) * gridSize, 0x00, 0xFF, 0xFF, 0x00);
    }
    else {
        drawOutlineSquare(activeX * gridSize - posX, activeY * gridSize - posY, 0xFF, 0x00, 0x00, 0x00);
        renderTileSelector();
    }
    SDL_RenderPresent(windowRenderer);
}

void EditorWindow::setRoom(Room * room)
{
    activeRoom = room;
}


void EditorWindow::drawOutlineSquare(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_Rect outlineRect = { x, y, gridSize, gridSize };
    SDL_SetRenderDrawColor(windowRenderer, r,g,b,a);
    SDL_RenderDrawRect(windowRenderer, &outlineRect);
}

void EditorWindow::drawSolidSquare(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_Rect fillRect = { x, y, gridSize, gridSize };
    SDL_SetRenderDrawColor(windowRenderer, r, g, b, a);
    SDL_RenderFillRect(windowRenderer, &fillRect);
}

void EditorWindow::updateTileSelector(int deltaX, int deltaY)
{
    if (tileSelector.posX + tileSelector.dimX + deltaX <= 16 && tileSelector.posX + deltaX >= 0) tileSelector.posX += deltaX;
    if (tileSelector.posY + tileSelector.dimY + deltaY <= 16 && tileSelector.posY + deltaY >= 0) tileSelector.posY += deltaY;
}

//This function does not work atm!!!
void EditorWindow::setActiveTileCoordinates()
{
    int x = 0;
    int y = 0;
    getMouseCoordinates(&x, &y);
    x /= scale_x;
    y /= scale_y;
    activeX = (x + posX) / (gridSize);
    activeY = (y + posY) / (gridSize);
    //Fix negative integer division off by one error
    if (x + posX < 0) activeX--;
    if (y + posY < 0) activeY--;
}

void EditorWindow::renderTileSelector()
{
    //Render available tiles
    for (int i = tileSelector.posX; i < tileSelector.posX + tileSelector.dimX; i++) {
        for (int j = tileSelector.posY; j < tileSelector.posY + tileSelector.dimY; j++) {
            TextureManager::tileMap.texture.renderTile((i - tileSelector.posX) * gridSize,(j - tileSelector.posY) * gridSize, i + j * 16);
        }
    }
    //Render delete button
    TextureManager::miscallenous[0].render(0, tileSelector.dimX * gridSize);
    //Render selected outline
    if (selectedTile == -1) drawOutlineSquare(0, 4 * gridSize, 0x00, 0xFF, 0x00, 0x00);
    else drawOutlineSquare(((selectedTile % 16) - tileSelector.posX) * gridSize, ((selectedTile / 16) - tileSelector.posY) * gridSize, 0x00, 0xFF, 0x00, 0x00);
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

bool EditorWindow::withinSelector()
{
    int x = 0;
    int y = 0;
    getMouseCoordinates(&x, &y);
    //How many tiles
    int tileCount = TextureManager::TOTAL_TILE_TEXTURES;
    return (x < tileSelector.dimX * gridSize * scale_x && y < tileSelector.dimY * gridSize * scale_y) ||
        (x < gridSize * scale_x && y < (tileSelector.dimY + 1) * gridSize * scale_y);

}

void EditorWindow::setSelectedTile()
{
    int x = 0;
    int y = 0;
    getMouseCoordinates(&x, &y);
    if ((y / (gridSize * scale_y)) >= tileSelector.dimY) selectedTile = -1; 
    else {
        selectedTile = tileSelector.posX + (x / (gridSize * scale_x)) +
            16 * (tileSelector.posY + (y / (gridSize * scale_y)));
    }
}

int EditorWindow::getSelectedTile()
{
    return selectedTile;
}
