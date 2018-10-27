#pragma once
#include "UIElement.h"
#include "UIPanel.h"
#include <vector>

class UIMovable : public UIPanel {
public:
    UIMovable(int _positionX, int _positionY, int _width, int _height,
        int _layer);



protected:
    //To be called in derived classes instead of update
    virtual void derivedUpdate();

private:
    //Denotes if the movable is currently being dragged
    bool drag;
    //Position of mouse last frame, updated when dragged
    int lastMouseX, lastMouseY;


    void onMouseOver();
    void update();
    void onSelect();
};