#pragma once
#include "UISelector.h"
#include "math\polygon.h"
#include <vector>
#include <optional>

class UIColliderSelector : public UISelector {
public:
    UIColliderSelector(int _posx, int _posy, int _layer,
        unsigned int _columns, unsigned int _rows,
        Color _selectedColor = COLOR_GREEN, Color _hoverColor = COLOR_CYAN);

    std::optional<Polyshape> getPolygon() const;

    void renderSelected(int x, int y, Color color = COLOR_PURPLE);
private:
};