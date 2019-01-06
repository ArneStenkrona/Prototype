#include "UISelector.h"
#include "System\IO\inputManager.h"
#include "World\Tile.h"
#include "System\graphics\graphicsEngine.h"

UISelector* UISelector::activeSelector = NULL;

UISelector::UISelector(int _posx, int _posy, int _layer, 
                       unsigned int _columns, unsigned int _rows,
                       unsigned int _indexLimitX, unsigned int _indexLimitY,
                       const std::string _label,
                       Color _selectedColor, Color _hoverColor, unsigned int selectableSize)
    : UIElement(_posx, _posy, selectableSize * _columns,
      LABEL_HEIGHT + selectableSize * _rows, _layer, false),
      columns(_columns), rows(_rows),
      indexLimitX(_indexLimitX), indexLimitY(_indexLimitY), label(_label), 
      selectedIndex(0), hoverIndex(-1),
      selectedColor(_selectedColor), hoverColor(_hoverColor)
{
    activeSelector = this;
}

UISelector::~UISelector()
{
    for (unsigned int i = 0; i < selectables.size(); i++) {
        for (unsigned int j = 0; j < selectables[i].size(); j++) {
            delete(selectables[i][j]);
        }
    }
}

int UISelector::getSelectedIndex() const
{

    return selectedIndex;
}

void UISelector::getRotationAndFlip(int & rot, bool & h, bool & v)
{
    rot = rotation;
    h = flipH;
    v = flipV;
}

void UISelector::setSelected(int i)
{
    selectedIndex = i;

    rotation = 0;
    flipH = false;
    flipV = false;
}

void UISelector::renderSelected(int x, int y, Color color)
{
    SDL_Rect rect = { x, y, (int)Tile::TILE_SIZE, (int)Tile::TILE_SIZE };
    SDL_SetRenderDrawColor(GraphicsEngine::getActiveRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(GraphicsEngine::getActiveRenderer(), &rect);
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
    if ((int)(offset % indexLimitX) + columns + dx <= indexLimitX &&
        (int)(offset % indexLimitX) + dx >= 0) offset += dx;
    if ((int)(offset / indexLimitY) + rows + dy <= indexLimitY &&
        (int)(offset / indexLimitX) + dy >= 0) offset += indexLimitX * dy;
}

void UISelector::update()
{
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
    UIElement::drawSquare(width, 16, COLOR_BLACK, SOLID, ALIGN_UP);
    UIElement::renderTextBackdrop(label, COLOR_WHITE, ALIGN_UP, 0, 2, COLOR_DARK_GREY);

    if (isSelected()) {
        UIElement::drawSquare(width, height - LABEL_HEIGHT, { 66, 134, 244, 255 }, OUTLINE, ALIGN_DOWN, 0);
    }
}
