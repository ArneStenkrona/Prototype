#include "UISelectableTool.h"
#include "UIToolSelector.h"
#include "System\graphics\textureManager.h"
#include "System\IO\inputManager.h"

UISelectableTool::UISelectableTool(UIToolSelector * _selector, int _posX, int _posY, 
                                   unsigned int _layer, int _index, 
                                   Color _selectedColor, Color _hoverColor)
    : UISelectable(_selector, _posX, _posY, 32, 32, _layer, _index, _selectedColor, _hoverColor)
{
}

void UISelectableTool::render()
{
    UIElement::drawSquare(width, height, COLOR_PINK, SOLID_SQUARE, ALIGN_CENTER);
    derivedRender();
    UIElement::drawSquare(width, height, currentColor, OUTLINE_SQUARE);
}

void UISelectableTool::derivedRender()
{
    TextureManager::spriteSheets[TextureManager::TOOL_ICONS].renderTile(positionX, positionY, index);
}

void UISelectableTool::onSelect()
{
    setSelected(UISelector::getActiveSelector());
}

void UISelectableTool::onMouseOver()
{
    if (getKeyDown(MOUSE_LEFT) || getKeyDown(MOUSE_RIGHT)) {
        selector->setSelected(index);
        select();
        currentColor = selectedColor;
    }
    else {
        currentColor = hoverColor;
    }
}
