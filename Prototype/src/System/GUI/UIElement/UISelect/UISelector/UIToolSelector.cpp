#include "UIToolSelector.h"
#include "..\UISelectable\UISelectableTool.h"

const std::map<UIToolSelector::TOOL, std::string> UIToolSelector::toolDictionary = { {PLACE_TOOL, "PLACE"},
                                                                                     {DELETE_TOOL, "DELETE"} };

UIToolSelector::UIToolSelector(int _posx, int _posy, int _layer, 
                               Color _selectedColor, Color _hoverColor)
    : UISelector(_posx, _posy, _layer, 1, TOTAL_TOOLS, 1, TOTAL_TOOLS, "TOOLS", _selectedColor, _hoverColor, 32)
{
    selectables.resize(columns + 1);
    for (unsigned int i = 0; i < columns; i++) {
        selectables[i].resize(rows);
        for (unsigned int j = 0; j < rows; j++) {
            selectables[i][j] = new UISelectableTool(this,
                positionX + (i * 32),
                LABEL_HEIGHT + positionY + (j * 32),
                layer + 1, i + (indexLimitX * j));
        }
    }
}

void UIToolSelector::update()
{
}

void UIToolSelector::render()
{
    UIElement::drawSquare(width, 16, COLOR_BLACK, SOLID, ALIGN_UP);
    UIElement::renderTextBackdrop(getLabel(), COLOR_WHITE, ALIGN_UP, 0, 2, COLOR_DARK_GREY);
}
