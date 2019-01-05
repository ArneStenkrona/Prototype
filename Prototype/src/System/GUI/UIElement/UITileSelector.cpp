#include "UITileSelector.h"
#include "System\IO\inputManager.h"
#include "System\graphics\textureManager.h"
#include <algorithm> 
#include <iostream>
#include "System\graphics\graphicsEngine.h"

UITileSelector::UITileSelector(int _posx, int _posy, int _layer,
                              unsigned int _columns, unsigned int _rows,
                              Color _selectedColor, Color _hoverColor)
    : UISelector(_posx, _posy, _layer, _columns, _rows, Tile::TILES_PER_ROW, Tile::TILES_PER_COLUMN, "TILES", _selectedColor, _hoverColor), tileDim(1),
      selectedColor(_selectedColor), hoverColor(_hoverColor)
{
    selectables.resize(columns + 1);
    for (unsigned int i = 0; i < columns; i++) {
        selectables[i].resize(rows);
        for (unsigned int j = 0; j < rows; j++) {
            selectables[i][j] = new UISelectableTile(this, 
                                                    positionX + (i * Tile::TILE_SIZE), 
                                                    LABEL_HEIGHT + positionY + (j * Tile::TILE_SIZE),
                                                    layer + 1, i + (indexLimitX * j));
        }
    }
    updateSelectedIndices();
}

Tile * UITileSelector::getTile() const
{
    Tile *tile;
    if (selectedIndex == indexLimitX * indexLimitY)
        tile = NULL;
    else
        tile = new Tile(selectedIndex, rotation, flipH, flipV);
    return tile;
}

std::vector<std::vector<Tile*>> UITileSelector::getTiles() const
{
    std::vector<std::vector<Tile*>> tiles;

    tiles.resize(tileDim);

    for (unsigned int i = 0; i < tileDim; i++) {
        tiles[i].resize(tileDim);
    }
    for (unsigned int i = 0; i < tileDim; i++) {
        for (unsigned int j = 0; j < tileDim; j++) {
            int ix = i;
            int iy = j;
            for (int r = 0; r < rotation; r++) {
                int temp = ix;
                ix = (tileDim - 1) - iy;
                iy = temp;
            }

            if (rotation % 2 == 0) {
                if (flipH)
                    ix = tileDim - 1 - ix;
                if (flipV)
                    iy = tileDim - 1 - iy;
            }
            else {
                if (flipV)
                    ix = tileDim - 1 - ix;
                if (flipH)
                    iy = tileDim - 1 - iy;
            }

            Tile *tile;
            tile = new Tile(selectedIndex + i + (indexLimitX * j),
                            rotation, flipH, flipV);
            tiles[ix][iy] = tile;
        }
    }
    return tiles;
}

void UITileSelector::renderSelected(int x, int y, Color color)
{
    TextureManager::tileMap.texture.renderTile(x, y, selectedIndex,
                                               tileDim, tileDim, flipH, flipV,
                                               rotation * 90, 
                                               (tileDim * Tile::TILE_SIZE) / 2 , 
                                               (tileDim * Tile::TILE_SIZE) / 2,
                                               color, false);

    SDL_Rect rect = { x, y, (int)tileDim * (int)Tile::TILE_SIZE, (int)tileDim * (int)Tile::TILE_SIZE };
    SDL_SetRenderDrawColor(GraphicsEngine::getActiveRenderer(), 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(GraphicsEngine::getActiveRenderer(), &rect);
}

bool UITileSelector::withinSelection(int idx)
{
    return selectedIndices.find(idx) != selectedIndices.end();
}

bool UITileSelector::withinHover(int idx)
{
    return hoverIndices.find(idx) != hoverIndices.end();
}

bool UITileSelector::getBorderColorAndType(int index, Color & c, int & b)
{
    int i; //Either hoverIndex or selectedIndex
    unsigned int j; 
    if (withinHover(index)) {
        c = hoverColor;
        i = hoverIndex;
        j = index;
    }
    else if (withinSelection(index + getOffset())) {
        c = selectedColor;
        i = selectedIndex;
        j = index + getOffset();
    }
    else {
        return false;
    }

    //Full border
    if (tileDim == 1) {
        b = 0;
        return true;
    }
    //Topleft border
    if (j == i) {
        b = 1;
        return true;
    }
    //Topright border
    if (j == i + tileDim - 1) {
        b = 2;
        return true;
    }
    //Bottomright border
    if (j == i + (tileDim - 1) + ((tileDim - 1) * indexLimitX)) {
        b = 3;
        return true;
    }
    //Bottomleft border
    if (j == i + ((tileDim - 1) * indexLimitX)) {
        b = 4;
        return true;
    }
    //Top border
    if (j < i + tileDim - 1) {
        b = 5;
        return true;
    }
    //Right border
    if (j % indexLimitX == (i + tileDim - 1) % indexLimitX) {
        b = 6;
        return true;
    }
    //Bottom border
    if (j / indexLimitX == (i / indexLimitX) + tileDim - 1) {
        b = 7;
        return true;
    }
    //Left border
    if (j % indexLimitX == i % indexLimitX) {
        b = 8;
        return true;
    }
    return false;
}

void UITileSelector::updateSelectedIndices()
{
    selectedIndices.clear();
    for (unsigned int i = 0; i < tileDim; i++) {
        for (unsigned int j = 0; j < tileDim; j++) {
            selectedIndices.insert(selectedIndex + i + j * indexLimitX);
        }
    }
}

void UITileSelector::updateHoverIndices()
{
    hoverIndices.clear();
    for (unsigned int i = 0; i < tileDim; i++) {
        for (unsigned int j = 0; j < tileDim; j++) {
            hoverIndices.insert(hoverIndex + i + j * indexLimitX);
        }
    }
}

void UITileSelector::clearHoverIndices()
{
    hoverIndices.clear();
}

void UITileSelector::update()
{
    UISelector::update();
    if (getActiveSelector() == this) {
        if (getKeyDown(INPUT_KEY_KP_MINUS) && tileDim > 1) {
            tileDim--;
            updateSelectedIndices();
        }
        if (getKeyDown(INPUT_KEY_KP_PLUS) && tileDim < std::min(rows, columns)) {
            tileDim++;
            updateSelectedIndices();
        }
    }
}

void UITileSelector::render()
{
    UISelector::render();

}

void UITileSelector::setSelected(int i)
{
    int diffX = indexLimitX - (i % indexLimitX) - tileDim;
    if (diffX < 0) i += diffX;
    int diffY = indexLimitY - (i / indexLimitX) - tileDim;
    if (diffY < 0) i += diffY * indexLimitX;
    UISelector::setSelected(i);
    updateSelectedIndices();
}

void UITileSelector::setHoverIndex(int i)
{
    int diffX = indexLimitX - ((i + offset) % indexLimitX) - tileDim;
    if (diffX < 0) i += diffX;
    int diffY = indexLimitY - ((i + offset) / indexLimitX) - tileDim;
    if (diffY < 0) i += diffY * indexLimitX;
    UISelector::setHoverIndex(i);
    updateHoverIndices();
}
