#include "UIComponent.h"
#include "..\UIPanel\UIPanel.h"

UIComponent::UIComponent(int _posx, int _posy, unsigned int _width, unsigned int _height, int _layer)
    :UIElement(_posx, _posy, _width, _height, _layer, true)
{
}

void UIComponent::onMouseOver()
{
    if (panel != nullptr)
        panel->onMouseOver();
}
