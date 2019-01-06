#include "UISelectableTool.h"
#include "UIToolSelector.h"
#include "System\graphics\textureManager.h"
#include "System\IO\inputManager.h"

UISelectableTool::UISelectableTool(UIToolSelector * _selector, int _posX, int _posY, 
                                   unsigned int _layer, int _index)
    : UISelectable(_selector, _posX, _posY, 32, 32, _layer, _index)
{
}

void UISelectableTool::render()
{

    UIElement::drawSquare(width, height, COLOR_PINK, SOLID, ALIGN_CENTER);
    UIElement::drawSquare(width, height, COLOR_BLACK, SOLID, ALIGN_CENTER);
    TextureManager::spriteSheets[TextureManager::TOOL_ICONS].renderTile(positionX, positionY, index, 2, 2);

    Color borderColor = mouseOver() ? selector->hoverColor :
        (selector->getSelectedIndex() == (int)(index + selector->getOffset()) ? selector->selectedColor : COLOR_NONE);
    UIElement::drawSquare(width, height, borderColor, OUTLINE);

}

void UISelectableTool::onSelect()
{
    setSelected(UISelector::getActiveSelector());
}

void UISelectableTool::onMouseOver()
{
    if (getKeyDown(MOUSE_LEFT) || getKeyDown(MOUSE_RIGHT)) {
        selector->setSelected(index + selector->offset);
        select();
    }
}
