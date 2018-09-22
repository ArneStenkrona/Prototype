#pragma once
#include "UIElement.h"
#include "math\polygon.h"

class UIColliderSelector;
class UISelectCollider : public UIElement {
public:
    UISelectCollider(UIColliderSelector* _selector, int _posx, int _posy,
                       unsigned int _layer, int _colliderIndex);

    void setColliderIndex(int index) { polygonIndex = index; }

    bool selected;
private:
    int polygonIndex;

    //border colors
    unsigned char r, g, b, a;

    void render();
    //called if mouse is over
    void onMouseOver();
    //unconditional update
    void update();

    UIColliderSelector* selector;

    static std::vector<Polyshape> polygons;
};