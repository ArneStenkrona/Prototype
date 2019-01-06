#pragma once
#include "UISelectable.h"

class UIObjectSelector;
class UISelectableObject : public UISelectable {
public:
    UISelectableObject(UIObjectSelector* _selector, int _posX, int _posY, unsigned int _layer,
        int _index);

private:
    void render();
};