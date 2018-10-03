#include "UISelectable.h"
#include "UISelector.h"
#include "System\IO\inputManager.h"

UISelectable::UISelectable(UISelector * _selector, int _posX, int _posY, unsigned int _width, unsigned int _height,
                            unsigned int _layer, int _index, Color _selectedColor, Color _hoverColor)
    : UIElement(_posX, _posY, _width, _height, _layer, true), 
      selector(_selector), index(_index), selectedColor(_selectedColor), hoverColor(_hoverColor)
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
    UIElement::drawOutlineSquare(currentColor);
    if (!selector->isActive())
        UIElement::drawSolidSquare({255,255,255,40});
}

void UISelectable::onMouseOver()
{
    if (getKeyDown(MOUSE_LEFT)) {
        selector->setActive();
        selector->setSelected(index);
        select();
        currentColor = selectedColor;
    }
    else {
        currentColor = hoverColor;
    }
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