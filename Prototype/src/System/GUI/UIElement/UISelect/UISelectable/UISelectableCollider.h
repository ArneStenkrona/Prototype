#pragma once
#include "UISelectable.h"
#include "math\polygon.h"

class UISelectableCollider : public UISelectable {
public:
    UISelectableCollider(UISelector* _selector, int _posX, int _posY, unsigned int _layer,
        int _index);
private:
    void render();
};