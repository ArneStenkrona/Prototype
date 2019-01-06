#pragma once
#include "math\point.h"
#include <vector>
#include <set>
#include "System\graphics\color.h"

enum Alignment {
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
enum Fill_Type {
    SOLID,
    OUTLINE
};
class UIElement {
public:
    // _posx, posy - position of the element
    // _width, _height - dimensions of the element
    // _layer - layer of the element, affects rendering order
    // _tangible - determines if the element can be interacted with
    // _visible - determines if the element should be rendered
    UIElement(int _posx, int _posy, unsigned int _width, unsigned int _height, unsigned int _layer, bool _tangible, bool _visible = true);
    virtual ~UIElement();

    int positionX, positionY;
    const unsigned int width, height;
    //Updates the state of all UIElements
    static void updateUIElements();
    //Renders all UIElements
    static void renderUIElements();
    //Checks if element is selected
    inline bool isSelected() const { return selectedElement == this; }
    static void setSelected(UIElement* element);
    static UIElement* getSelected() { return selectedElement; }

    inline bool mouseOver() const { return lastMouseOverElement == this; }

    inline unsigned int getID() const { return ID; }

    //Moves UIElement to the front of a different layer
    void moveToFrontOffLayer(unsigned int l);
protected:
    //Identifies the element
    const unsigned int ID;
    //The layer this element belongs to
    unsigned int layer;
    //If the element can be clicked/hovered over
    bool tangible;
    //If the element should be rendered
    bool visible;

    virtual void render();
    //called if mouse enters
    virtual void onMouseEnter();
    //called if mouse is over
    virtual void onMouseOver();
    //called if mouse leaves
    virtual void onMouseExit();
    //called if selected
    virtual void onSelect();
    //called if deselected
    virtual void onDeselect();
    //unconditional update
    virtual void update();

    //takes alignment and width and height of image to be rendered
    //returns alignment offset parameters
    void getAlignmentOffset(Alignment align, int _width, int _height, int &alignx, int &aligny) const;
    //Draws square at position of UIElement
    void drawSquare(int _width, int _height, Color color = { 255,255,255,255 }, Fill_Type type = SOLID,
                    Alignment align = ALIGN_NONE, int offsetX = 0, int offsetY = 0) const;

    void drawCircle(int diameter, Color color = { 255,255,255,255 }, Fill_Type type = SOLID,
                    Alignment align = ALIGN_NONE, int offsetX = 0, int offsetY = 0) const;

    //Renders text at position
    void renderText(std::string text, Color color = { 255,255,255,255 }, Alignment align = ALIGN_NONE, int offsetX = 0, int offsetY = 0) const;
    //Renders text at position, with backdrop
    void renderTextBackdrop(std::string text, Color color = { 255,255,255,255 }, Alignment align = ALIGN_NONE, int offsetX = 0, int offsetY = 0, Color backColor = COLOR_BLACK) const;


private:
    //Container for all UIElements, divided by layer
    static std::vector<std::vector<UIElement*>> allUIElements;
    //Currently selected element (last clicked on)
    static UIElement* selectedElement;
    //Total number of elements
    static unsigned int NumberOfElements;

    static UIElement* lastMouseOverElement;
    static UIElement* mouseOverElement;
};