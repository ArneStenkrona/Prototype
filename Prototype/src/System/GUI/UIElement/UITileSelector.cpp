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
                                     layer, i + (16 * j), _selectedColor, _hoverColor);
        }
    }
    selectables[columns].resize(1);
    selectables[columns][0] = new UISelectableTile(this, positionX + (columns * 32), positionY,
                                   layer, -1, _selectedColor, _hoverColor);
}

UITileSelector::~UITileSelector()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            delete(selectables[i][j]);
        }
    }
}

void UITileSelector::getRotationAndFlip(int & rot, bool & h, bool & v)
{
    rot = rotation;
    h = flipH;
    v = flipV;
}

Tile * UITileSelector::getTile() const
{
    Tile *tile;
    if (selectedIndex == -1)
        tile = NULL;
    else
        tile = new Tile(selectedIndex, rotation, flipH, flipV);
    return tile;
}

void UITileSelector::derivedUpdate()
{
    if (getActiveSelector() == this) {
        if (getKeyDown(INPUT_KEY_R))
            rotation = (rotation + 1) % 4;

        if (getKeyDown(INPUT_KEY_F))
            flipH = !flipH;

        if (getKeyDown(INPUT_KEY_G))
            flipV = !flipV;
    }
}
