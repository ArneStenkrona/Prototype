#include "UIToolSelector.h"
#include "UISelectableTool.h"

UIToolSelector::UIToolSelector(int _posx, int _posy, int _layer, 
                               unsigned int _columns, unsigned int _rows, 
                               Color _selectedColor, Color _hoverColor)
    : UISelector(_posx, _posy, _layer, _columns, _rows, 16, 16, "TOOLS")
{
    selectables.resize(columns + 1);
    for (int i = 0; i < columns; i++) {
        selectables[i].resize(rows);
        for (int j = 0; j < rows; j++) {
            selectables[i][j] = new UISelectableTool(this,
                positionX + (i * 32),
                LABEL_HEIGHT + positionY + (j * 32),
                layer + 1, i + (indexLimitX * j),
                _selectedColor, _hoverColor);
        }
    }
}
