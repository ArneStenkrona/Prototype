#pragma once
#include "UIElement.h"
#include "UISelectable.h"
#include <vector>

class UISelector : public UIElement {
public:
    UISelector(int _posx, int _posy, int _layer,
        unsigned int _columns, unsigned int _rows, 
        unsigned int _indexLimitX, unsigned int _indexLimitY);
    ~UISelector();

    inline static UISelector* getActiveSelector() { return activeSelector; }
    inline UISelectable* getSelected() const { return selected; }
protected:
    //updates before regular update()
    virtual void derivedUpdate();
    //Selected selectable
    UISelectable* selected;
    //All UISelectables in layout
    std::vector<std::vector<UISelectable*>> selectables;
    //columns and rows in layout
    unsigned int columns, rows;
    //index offsets
    int indX, indY;
private:
    //selected UISelectable
    void setSelected(UISelectable* s);
    void setActive();
    //Dimensions of whatever data-structure is being selected
    unsigned int indexLimitX, indexLimity;

    void moveIndices(int dx, int dy);

    void update();

    static UISelector* activeSelector;

    friend class UISelectable;
};