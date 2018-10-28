#include "UIObjectSelector.h"
#include "UISelectableObject.h"
#include "System\graphics\textureManager.h"

UIObjectSelector::UIObjectSelector(int _posx, int _posy, int _layer, unsigned int _columns, unsigned int _rows, Color _selectedColor, Color _hoverColor)
    :UISelector(_posx, _posy, _layer, _columns, _rows, 16, 16, "OBJECTS")
{
    selectables.resize(columns + 1);
    for (int i = 0; i < columns; i++) {
        selectables[i].resize(rows);
        for (int j = 0; j < rows; j++) {
            selectables[i][j] = new UISelectableObject(this,
                positionX + (i * 32),
                LABEL_HEIGHT + positionY + (j * 32),
                layer + 1, i + (indexLimitX * j),
                _selectedColor, _hoverColor);
        }
    }
}

UIObjectSelector::~UIObjectSelector()
{
}

Object * UIObjectSelector::getObject() const
{
    return nullptr;
}

void UIObjectSelector::renderSelected(int x, int y, Color color)
{
        TextureManager::spriteSheets[TextureManager::OBJECT_ICONS].renderTile(x, y, selectedIndex,
                                                                   1, 1, flipH, flipV,
                                                                   rotation * 90, 16, 16,
                                                                   color);
}
