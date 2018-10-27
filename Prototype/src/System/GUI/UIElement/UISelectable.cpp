#include "UISelectable.h"
#include "UISelector.h"
#include "System\IO\inputManager.h"

UISelectable::UISelectable(UISelector * _selector, int _posX, int _posY, unsigned int _width, unsigned int _height,
                            unsigned int _layer, int _index, Color _selectedColor, Color _hoverColor)
    : UIElement(_posX, _posY, _width, _height, _layer, true), 
      selector(_selector), index(_index), selectedColor(_selectedColor), hoverColor(_hoverColor)
{
}

UISelectable::~UISelectable()
{
}

void UISelectable::derivedRender()
{
}

void UISelectable::derivedUpdate()
{
}

void UISelectable::select()
{
}

void UISelectable::render()
{
    derivedRender();
    UIElement::drawSquare(width, height, currentColor, OUTLINE_SQUARE);
    if (!selector->isActive())
        UIElement::drawSquare(width, height, {255,255,255,40});
}

void UISelectable::onMouseOver()
{
    if (getKeyDown(MOUSE_LEFT) || getKeyDown(MOUSE_RIGHT)) {
        selector->setActive();
        selector->setSelected(index);
        select();
        currentColor = selectedColor;
    }
    else {
        currentColor = hoverColor;
    }
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
    derivedUpdate();
    if (selector->getSelectedIndex() == index) {
        currentColor = selectedColor;
    }
    else {
        currentColor = COLOR_NONE;
    }
}