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
    inline int getSelected() const { return selectedIndex; }
protected:
    //selected UISelectable
    void setSelected(int i);
    //Called after setSelected()
    virtual void derivedSetSelected(int i);
    //updates before update()
    virtual void derivedUpdate();

    //All UISelectables in layout
    std::vector<std::vector<UISelectable*>> selectables;
    //Selected index
    int selectedIndex;
    //columns and rows in layout
    unsigned int columns, rows;
    //index offsets
    int indX, indY;
    //Dimensions of the data structure that index is pointing at
    const unsigned int indexLimitX, indexLimity;

private:
    void setActive();
    //Dimensions of whatever data-structure is being selected

    void moveIndices(int dx, int dy);

    void update();

    static UISelector* activeSelector;

    friend class UISelectable;
};