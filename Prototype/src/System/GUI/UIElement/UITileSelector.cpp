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
            selectables[i][j] = new UISelectableTile(this, positionX + (i * 32), positionY + (j * 32),
                                     layer, i + (16 * j));
        }
    }
    selectables[columns].resize(1);
    selectables[columns][0] = new UISelectableTile(this, positionX + (columns * 32), positionY,
                                   layer, -1);
}

UITileSelector::~UITileSelector()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            delete(selectables[i][j]);
        }
    }
}

Tile * UITileSelector::getTile()
{
    //Forgive me for typecasting
    if ((UISelectableTile*)selected)
        return ((UISelectableTile*)selected)->getTile();
    else 
        return NULL;
}

