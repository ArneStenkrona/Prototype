#pragma once
#include "UIElement.h"
#include "UISelectCollider.h"
#include <vector>
class UIColliderSelector : public UIElement {
public:
    UIColliderSelector(int _posx, int _posy, int _layer,
        unsigned int _columns, unsigned int _rows);
    ~UIColliderSelector();

    inline unsigned int getSelectedIndex() const { return selectedColliderIndex; }
    void setIndex(unsigned int _index) { selectedColliderIndex = _index; }
    void moveIndices(int dx, int dy);
private:
    std::vector<std::vector<UISelectCollider*>> colliders;
    //selected tileIndex
    int selectedColliderIndex;
    //offset for indicies
    int indX, indY;
    unsigned int columns, rows;

    void update();
};