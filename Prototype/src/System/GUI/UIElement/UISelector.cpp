#include "UISelector.h"
#include "System\IO\inputManager.h"
#include "World\Tile.h"

UISelector* UISelector::activeSelector = NULL;

UISelector::UISelector(int _posx, int _posy, int _layer, 
                       unsigned int _columns, unsigned int _rows,
                       unsigned int _indexLimitX, unsigned int _indexLimitY)
    : UIElement(_posx, _posy, Tile::TILE_SIZE * _columns, Tile::TILE_SIZE * _rows, _layer, false), columns(_columns), rows(_rows),
      indexLimitX(_indexLimitX), indexLimity(_indexLimitY)
{
    activeSelector = this;
}

UISelector::~UISelector()
{
    selectables.clear();
}

void UISelector::derivedUpdate()
{
}

void UISelector::setSelected(int i)
{
    selectedIndex = i;
    derivedSetSelected(i);
}

void UISelector::derivedSetSelected(int i)
{
}

void UISelector::setActive()
{
    if (activeSelector != this) {
        activeSelector = this;
    }
}

void UISelector::moveIndices(int dx, int dy)
{
    if (indX + columns + dx <= indexLimitX && indX + dx >= 0) indX += dx;
    if (indY + rows + dy <= indexLimity && indY + dy >= 0) indY += dy;
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            selectables[i][j]->setIndex(indX + i + (indexLimitX * (indY + j)));
        }
    }
}

void UISelector::update()
{
    derivedUpdate();
    if (isSelected()) {
        int dX = 0;
        int dY = 0;

        if (getKeyDown(INPUT_KEY_W)) {
            dY -= 1;
        }
        if (getKeyDown(INPUT_KEY_S)) {
            dY += 1;
        }
        if (getKeyDown(INPUT_KEY_A)) {
            dX -= 1;
        }
        if (getKeyDown(INPUT_KEY_D)) {
            dX += 1;
        }
        if (dX || dY) moveIndices(dX, dY);
    }

}