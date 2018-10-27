#pragma once
#include "UISelector.h"
#include "UISelectable.h"

class UIToolSelector : public UISelector {
public:
    UIToolSelector(int _posx, int _posy, int _layer,
        Color _selectedColor = COLOR_GREEN, Color _hoverColor = COLOR_CYAN);
private:
    void update();
    void render();

    friend class UISelectable;
};
