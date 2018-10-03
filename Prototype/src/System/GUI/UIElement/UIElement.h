#pragma once
#include "math\point.h"
#include <vector>
#include <set>
#include "System\graphics\color.h"

static enum ALIGNMENT {
    ALIGN_UP,
    ALIGN_DOWN,
    ALIGN_LEFT,
    ALIGN_RIGHT,
    ALIGN_CENTER,
    ALIGN_NONE
};

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
    //Renders text at position
    inline void renderText(int offsetX, int offsetY, std::string text)
    { renderText(offsetX, offsetY, text, ALIGN_NONE, { 255,255,255,255 }); }
    inline void renderText(int offsetX, int offsetY, std::string text, Color color)
    { renderText(offsetX, offsetY, text, ALIGN_NONE, color); }
    inline void renderText(int offsetX, int offsetY, std::string text, ALIGNMENT align = ALIGN_CENTER)
    { renderText(offsetX, offsetY, text, align, { 255,255,255,255 }); }
    void renderText(int offsetX, int offsetY, std::string text, ALIGNMENT align, Color color) const;
};