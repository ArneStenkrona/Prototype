#pragma once
#include "UISelectable.h"

class UIToolSelector;
class UISelectableTool : public UISelectable {
public:
    UISelectableTool(UIToolSelector* _selector, int _posX, int _posY, unsigned int _layer,
        int _index);
private:
    void render();

    void onSelect();

    void onMouseOver();
};