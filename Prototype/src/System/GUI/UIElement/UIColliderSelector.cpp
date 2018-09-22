#include "UIColliderSelector.h"
#include "System\IO\inputManager.h"
#include "UISelectableCollider.h"

UIColliderSelector::UIColliderSelector(int _posx, int _posy, int _layer, 
                                       unsigned int _columns, unsigned int _rows,
                                       Color _selectedColor, Color _hoverColor)
    : UISelector(_posx, _posy, _layer, _columns, _rows, 8, 8)
{
    selectables.resize(columns + 1);
    for (int i = 0; i < columns; i++) {
        selectables[i].resize(rows);
        for (int j = 0; j < rows; j++) {
            selectables[i][j] = new UISelectableCollider(this, positionX + (i * 32), positionY + (j * 32),
                                                         layer, i + (16 * j), _selectedColor, _hoverColor);
        }
    }
}

UIColliderSelector::~UIColliderSelector()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            delete(selectables[i][j]);
        }
    }
}

Polyshape * UIColliderSelector::getPolygon() const
{
    if (Polyshape::basicPolygons.size() > selectedIndex)
        return &Polyshape::basicPolygons[selectedIndex];
    else
        return NULL;
}