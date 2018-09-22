#pragma once
#include "UISelectable.h"
#include "math\polygon.h"

class UISelectableCollider : public UISelectable {
public:
    UISelectableCollider(UISelector* _selector, int _posX, int _posY, unsigned int _layer,
        int _index, Color _selectedColor = COLOR_PURPLE, Color _hoverColor = COLOR_CYAN);

    //Creates and returns a polygon based on member values
    Polyshape* getPolygon();
private:
    void derivedRender();
    void derivedUpdate();
};