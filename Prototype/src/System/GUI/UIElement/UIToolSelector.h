#pragma once
#include "UISelector.h"

class UIToolSelector : public UISelector {
public:
    UIToolSelector(int _posx, int _posy, int _layer,
        unsigned int _columns, unsigned int _rows,
        Color _selectedColor = COLOR_GREEN, Color _hoverColor = COLOR_CYAN);
private:
};