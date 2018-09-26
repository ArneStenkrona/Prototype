#pragma once
#include "math\point.h"
#include <vector>
#include <set>
#include "System\graphics\color.h"

class UIElement {
public:
    UIElement(int _posx, int _posy, int _width, int _height, int _layer, bool _visible);
    ~UIElement();

    int positionX, positionY;
    int width, height;
    //Updates the state of all UIElements
    static void updateUIElements();
    //Renders all UIElements
    static void renderUIElements();
protected:
    //Container for all UIElements, divided by layer
    static std::vector<std::set<UIElement*>> allUIElements;
    
    int layer;
    bool visible;

    virtual void render();
    //called if mouse is over
    virtual void onMouseOver();
    //unconditional update
    virtual void update();
    //Draws squares at position, and width dimensions, of UIElement
    void drawOutlineSquare(Color color);
    void drawSolidSquare(Color color);
};