#include "UITileSelector.h"
#include "System\IO\inputManager.h"
#include "System\graphics\textureManager.h"

UITileSelector::UITileSelector(int _posx, int _posy, int _layer,
                              unsigned int _columns, unsigned int _rows,
                              Color _selectedColor, Color _hoverColor)
    : UISelector(_posx, _posy, _layer, _columns, _rows, 16, 16, "TILES"), tileDim(1)
{
    selectables.resize(columns + 1);
    for (int i = 0; i < columns; i++) {
        selectables[i].resize(rows);
        for (int j = 0; j < rows; j++) {
            selectables[i][j] = new UISelectableTile(this, 
                                                    positionX + (i * Tile::TILE_SIZE), 
                                                    LABEL_HEIGHT + positionY + (j * Tile::TILE_SIZE),
                                                    layer + 1, i + (indexLimitX * j), 
                                                    _selectedColor, _hoverColor);
        }
    }
}

Tile * UITileSelector::getTile() const
{
    Tile *tile;
    if (selectedIndex == indexLimitX * indexLimity)
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

void UITileSelector::update()
{
    if (getKeyDown(INPUT_KEY_KP_MINUS) && tileDim > 1)
        tileDim--;
    if (getKeyDown(INPUT_KEY_KP_PLUS) && tileDim < 4)
        tileDim++;
}
