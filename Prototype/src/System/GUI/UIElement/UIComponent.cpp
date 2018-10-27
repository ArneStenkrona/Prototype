#include "UIComponent.h"
#include "UIPanel.h"

UIComponent::UIComponent(int _posx, int _posy, int _width, int _height, int _layer)
    :UIElement(_posx, _posy, _width, _height, _layer, true)
{
}

void UIComponent::onMouseOver()
{
    if (panel)
        panel->onMouseOver();
}
