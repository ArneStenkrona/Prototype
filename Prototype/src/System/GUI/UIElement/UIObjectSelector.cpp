#include "UIObjectSelector.h"
#include "UISelectableObject.h"

UIObjectSelector::UIObjectSelector(int _posx, int _posy, int _layer, unsigned int _columns, unsigned int _rows, Color _selectedColor, Color _hoverColor)
    :UISelector(_posx, _posy, _layer, _columns, _rows, 16, 16)
{
    selectables.resize(columns + 1);
    for (int i = 0; i < columns; i++) {
        selectables[i].resize(rows);
        for (int j = 0; j < rows; j++) {
            selectables[i][j] = new UISelectableObject(this,
                positionX + (i * 32),
                positionY + (j * 32),
                layer + 1, i + (indexLimitX * j),
                _selectedColor, _hoverColor);
        }
    }
    selectables[columns].resize(1);
    selectables[columns][0] = new UISelectableObject(this, positionX + (columns * 32), positionY,
        layer + 1, indexLimitX * indexLimity, _selectedColor, _hoverColor);
}

UIObjectSelector::~UIObjectSelector()
{
}

Object * UIObjectSelector::getObject() const
{
    return nullptr;
}