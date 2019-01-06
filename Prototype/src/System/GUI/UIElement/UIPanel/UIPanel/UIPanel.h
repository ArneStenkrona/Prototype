#pragma once
#include "..\UIComponent\UIComponent.h"

class UIPanel : public UIElement {
public:
    UIPanel(int _positionX, int _positionY, int _width, int _height,
        int _layer);

    ~UIPanel();

    void attach(UIComponent* c, Alignment a, int offsetX, int offsetY);

    //Checks if element is selected
    bool isSelected() const;

protected:

    //UIElements attached to this panel
    //These will be destroyed when UIPanel is deleted
    std::vector<UIComponent*> attached;
    //Toggles selected from attached
    void toggleSelected();

    void update();

    friend class UIComponent;
};