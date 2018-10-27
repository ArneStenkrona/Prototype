#include "UITileSelector.h"
#include "System\IO\inputManager.h"

UITileSelector::UITileSelector(int _posx, int _posy, int _layer,
                              unsigned int _columns, unsigned int _rows,
                              Color _selectedColor, Color _hoverColor)
    : UISelector(_posx, _posy, _layer, _columns, _rows, 16, 16)
{
    selectables.resize(columns + 1);
    for (int i = 0; i < columns; i++) {
        selectables[i].resize(rows);
        for (int j = 0; j < rows; j++) {
            selectables[i][j] = new UISelectableTile(this, 
                                                    positionX + (i * Tile::TILE_SIZE), 
                                                    positionY + (j * Tile::TILE_SIZE),
                                                    layer + 1, i + (indexLimitX * j), 
                                                    _selectedColor, _hoverColor);
        }
    }
    selectables[columns].resize(1);
    selectables[columns][0] = new UISelectableTile(this, positionX + (columns * Tile::TILE_SIZE), positionY,
                                                   layer + 1, indexLimitX * indexLimity, _selectedColor, _hoverColor);
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
