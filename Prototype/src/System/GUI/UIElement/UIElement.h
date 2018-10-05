#pragma once
#include "math\point.h"
#include <vector>
#include <set>
#include "System\graphics\color.h"

static enum Alignment {
    ALIGN_UP,
    ALIGN_DOWN,
    ALIGN_LEFT,
    ALIGN_RIGHT,
    ALIGN_CENTER,
    ALIGN_UPPER_LEFT,
    ALIGN_UPPER_RIGHT,
    ALIGN_LOWER_LEFT,
    ALIGN_LOWER_RIGHT,
    ALIGN_NONE
};
static enum Square_type {
    SOLID_SQUARE,
    OUTLINE_SQUARE
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
    //Checks if element is selected
    inline bool isSelected() const { return selectedElement == this; }
    static void setSelected(UIElement* element);
protected:
    
    int layer;
    bool visible;

    virtual void render();
    //called if mouse is over
    virtual void onMouseOver();
    //called if selected
    virtual void onSelect();
    //called if deselected
    virtual void onDeselect();
    //unconditional update
    virtual void update();

    //takes alignment and width and height of image to be rendered
    //returns alignment offset parameters
    void getAlignmentOffset(Alignment align, int _width, int _height, int &alignx, int &aligny) const;
    //Draws square at position, and width dimensions, of UIElement
    void drawSquare(int _width, int _height, Color color, Square_type type = SOLID_SQUARE, 
                    Alignment align = ALIGN_NONE, int offsetX = 0, int offsetY = 0) const;

    //Renders text at position
    void renderText(std::string text, Color color = { 255,255,255,255 }, Alignment align = ALIGN_NONE, int offsetX = 0, int offsetY = 0) const;

private:
    //Container for all UIElements, divided by layer
    static std::vector<std::set<UIElement*>> allUIElements;
    //Currently selected element (last clicked on)
    static UIElement* selectedElement;
};