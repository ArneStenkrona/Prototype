#include "UISelectable.h"
#include "UISelector.h"
#include "System\IO\inputManager.h"

UISelectable::UISelectable(UISelector * _selector, int _posX, int _posY, unsigned int _width, unsigned int _height,
                            unsigned int _layer, int _index) 
    : UIElement(_posX, _posY, _width, _height, _layer, true),
      selector(_selector), index(_index)
{
}

UISelectable::~UISelectable()
{
}


void UISelectable::select()
{
}

void UISelectable::render()
{
    Color borderColor = mouseOver() ? selector->hoverColor :
        (selector->getSelectedIndex() == index + selector->offset ? selector->selectedColor : COLOR_NONE);

    UIElement::drawSquare(width, height, borderColor, OUTLINE_SQUARE);

    if (!selector->isActive())
        UIElement::drawSquare(width, height, { 255,255,255,40 });
}

void UISelectable::onMouseOver()
{
    if (getKeyDown(MOUSE_LEFT) || getKeyDown(MOUSE_RIGHT)) {
        selector->setActive();
        selector->setSelected(index + selector->offset);
        select();
    }
    else {
    }
    selector->setHoverIndex(index);
}

void UISelectable::onMouseLeft()
{
    selector->setHoverIndex(-1);
}

void UISelectable::onSelect()
{
    selector->selected = true;
}

void UISelectable::onDeselect()
{
    selector->selected = false;
}

void UISelectable::update() {
}