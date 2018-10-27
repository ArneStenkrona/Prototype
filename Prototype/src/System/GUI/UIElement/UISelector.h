#pragma once
#include "UIElement.h"
#include "UISelectable.h"
#include <vector>

class UISelector : public UIElement {
public:
    UISelector(int _posx, int _posy, int _layer,
        unsigned int _columns, unsigned int _rows, 
        unsigned int _indexLimitX, unsigned int _indexLimitY,
        const std::string _label);
    ~UISelector();

    inline static UISelector* getActiveSelector() { return activeSelector; }
    inline bool isActive() const { return activeSelector == this; }
    inline int getSelectedIndex() const { return selectedIndex; }

    void getRotationAndFlip(int &rot, bool &h, bool &v);

    static const unsigned int LABEL_HEIGHT = 16;

protected:
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
    //Transformations of selected
    int rotation;
    bool flipH, flipV;
    //selected UISelectable
    void setSelected(int i);
    //Called after setSelected()
    virtual void derivedSetSelected(int i);
    //updates before update()
    virtual void derivedUpdate();
    //Checks if element is selected
    inline bool isSelected() const { return selected; }

private:
    static UISelector* activeSelector;
    //Label of this selector
    const std::string label;
    //Height of the label

    //Is any UISelectable in selectables selected? Hacky solution to isSelected(), should be done in a less coupled way
    bool selected;

    void setActive();

    //move indices of all selected
    void moveIndices(int dx, int dy);

    void update();
    void render();

    friend class UISelectable;
};