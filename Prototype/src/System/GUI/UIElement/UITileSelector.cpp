#include "UITileSelector.h"
#include "System\IO\inputManager.h"
#include "System\graphics\textureManager.h"
#include <algorithm> 

UITileSelector::UITileSelector(int _posx, int _posy, int _layer,
                              unsigned int _columns, unsigned int _rows,
                              Color _selectedColor, Color _hoverColor)
    : UISelector(_posx, _posy, _layer, _columns, _rows, 16, 16, "TILES", _selectedColor, _hoverColor), tileDim(1),
      selectedColor(_selectedColor), hoverColor(_hoverColor)
{
    selectables.resize(columns + 1);
    for (int i = 0; i < columns; i++) {
        selectables[i].resize(rows);
        for (int j = 0; j < rows; j++) {
            selectables[i][j] = new UISelectableTile(this, 
                                                    positionX + (i * Tile::TILE_SIZE), 
                                                    LABEL_HEIGHT + positionY + (j * Tile::TILE_SIZE),
                                                    layer + 1, i + (indexLimitX * j));
        }
    }
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

void UITileSelector::renderSelected(int x, int y, Color color)
{
        TextureManager::tileMap.texture.renderTile(x, y, selectedIndex,
                                                   1, 1, flipH, flipV,
                                                   rotation * 90, 16, 16,
                                                   color);
}

bool UITileSelector::withinSelection(int idx)
{
    return selectedIndices.find(idx) != selectedIndices.end();
}

bool UITileSelector::withinHover(int idx)
{
    return hoverIndices.find(idx) != hoverIndices.end();
}

void UITileSelector::updateSelectedIndices()
{
    selectedIndices.clear();
    for (int i = 0; i < tileDim; i++) {
        for (int j = 0; j < tileDim; j++) {
            selectedIndices.insert(selectedIndex + i + j * indexLimitX);
        }
    }
}

void UITileSelector::updateHoverIndices()
{
    hoverIndices.clear();
    for (int i = 0; i < tileDim; i++) {
        for (int j = 0; j < tileDim; j++) {
            hoverIndices.insert(hoverIndex + i + j * indexLimitX);
        }
    }
}

void UITileSelector::update()
{
    UISelector::update();
    if (getKeyDown(INPUT_KEY_KP_MINUS) && tileDim > 1) {
        tileDim--;
        updateSelectedIndices();
    }
    if (getKeyDown(INPUT_KEY_KP_PLUS) && tileDim < std::min(rows, columns)) {
        tileDim++;
        updateSelectedIndices();
    }
}

void UITileSelector::render()
{
    UISelector::render();

}

void UITileSelector::setSelected(int i)
{
    UISelector::setSelected(i);
    updateSelectedIndices();
}

void UITileSelector::setHoverIndex(int i)
{
    UISelector::setHoverIndex(i);
    updateHoverIndices();
}
