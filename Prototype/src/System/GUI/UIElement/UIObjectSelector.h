#pragma once
#include "UISelector.h"
#include "World\objects\object.h"

class UIObjectSelector : public UISelector {
public:
    UIObjectSelector(int _posx, int _posy, int _layer,
        unsigned int _columns, unsigned int _rows,
        Color _selectedColor = COLOR_GREEN, Color _hoverColor = COLOR_CYAN);
    ~UIObjectSelector();

    //Creates and returns an object based on selected
    Object* getObject() const;

    void renderSelected(int x, int y, Color color = COLOR_WHITE);

private:
};