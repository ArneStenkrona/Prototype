#pragma once
#include "UISelectable.h"

class UIToolSelector;
class UISelectableTool : public UISelectable {
public:
    UISelectableTool(UIToolSelector* _selector, int _posX, int _posY, unsigned int _layer,
        int _index, Color _selectedColor = COLOR_GREEN, Color _hoverColor = COLOR_CYAN);
private:
    void render();
    void derivedRender();

    void onSelect();

    void onMouseOver();
};