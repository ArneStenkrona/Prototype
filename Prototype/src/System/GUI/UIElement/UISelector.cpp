#include "UISelector.h"
#include "System\IO\inputManager.h"
#include "World\Tile.h"

UISelector* UISelector::activeSelector = NULL;

UISelector::UISelector(int _posx, int _posy, int _layer, 
                       unsigned int _columns, unsigned int _rows,
                       unsigned int _indexLimitX, unsigned int _indexLimitY,
                       const std::string _label)
    : UIElement(_posx, _posy, Tile::TILE_SIZE * _columns, LABEL_HEIGHT + Tile::TILE_SIZE * _rows, _layer, false), columns(_columns), rows(_rows),
      indexLimitX(_indexLimitX), indexLimity(_indexLimitY), label(_label)
{
    activeSelector = this;
}

UISelector::~UISelector()
{
    for (int i = 0; i < selectables.size(); i++) {
        for (int j = 0; j < selectables[i].size(); j++) {
            delete(selectables[i][j]);
        }
    }
}

void UISelector::getRotationAndFlip(int & rot, bool & h, bool & v)
{
    rot = rotation;
    h = flipH;
    v = flipV;
}


void UISelector::derivedUpdate()
{
}

void UISelector::setSelected(int i)
{
    selectedIndex = i;
    derivedSetSelected(i);

    rotation = 0;
    flipH = false;
    flipV = false;
}

void UISelector::derivedSetSelected(int i)
{
}

void UISelector::renderSelected(int x, int y, Color color)
{
}

void UISelector::onSelect()
{
    setActive();
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

    if (getActiveSelector() == this) {
        if (getKeyDown(INPUT_KEY_R))
            rotation = (rotation + 1) % 4;

        if (getKeyDown(INPUT_KEY_F))
            flipH = !flipH;

        if (getKeyDown(INPUT_KEY_G))
            flipV = !flipV;
    }

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

void UISelector::render()
{
    UIElement::drawSquare(width, 16, COLOR_BLACK, SOLID_SQUARE, ALIGN_UP);
    UIElement::renderTextBackdrop(label, COLOR_WHITE, ALIGN_UP, 0, 2, COLOR_DARK_GREY);

    if (isSelected())
        UIElement::drawSquare(width, height - LABEL_HEIGHT, { 66, 134, 244, 255 }, OUTLINE_SQUARE, ALIGN_DOWN, 0);
}
