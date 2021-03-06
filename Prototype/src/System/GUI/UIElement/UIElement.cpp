#include "UIElement.h"
#include "System\IO\inputManager.h"
#include "System\graphics\graphicsEngine.h"
#include <iostream>

std::vector<std::vector<UIElement*>> UIElement::allUIElements = std::vector<std::vector<UIElement*>>();
UIElement* UIElement::selectedElement = nullptr;
UIElement* UIElement::mouseOverElement = nullptr;
UIElement* UIElement::lastMouseOverElement = nullptr;
unsigned int UIElement::NumberOfElements = 0;

UIElement::UIElement(int _posx, int _posy, unsigned int _width, unsigned int _height,
                    unsigned int _layer, bool _tangible, bool _visible)
    : positionX(_posx), positionY(_posy), width(_width), height(_height), 
      layer(_layer), tangible(_tangible), visible(_visible), ID(NumberOfElements)
{
    if (allUIElements.size() < layer + 1) {
        allUIElements.resize(layer + 1);
    }
    allUIElements[layer].push_back(this);

    NumberOfElements++;
}

UIElement::~UIElement()
{
    vector<UIElement*>::iterator it = allUIElements[layer].begin();

    while (it != allUIElements[layer].end()) {

        if (*it == this) {

            it = allUIElements[layer].erase(it);
            break;
        }
        else ++it;
    }
    if (selectedElement == this)
        selectedElement = nullptr;
    if (mouseOverElement == this)
        mouseOverElement = nullptr;
    if (lastMouseOverElement == this) {
        lastMouseOverElement = nullptr;
    }
}

//helper function
inline bool pointWithin(int px, int py, int posx, int posy,
                        int dimx, int dimy) {
    return px >= posx && px < posx + dimx &&
        py >= posy && py < posy + dimy;
}

void UIElement::updateUIElements()
{

    //Element that mouse is over, if visible
    //If mouse is over more than one element it
    //will prioritize lowest layer number
    //If more than one have the lowest layer number
    //one of them will be picked according to
    //iterator order
    mouseOverElement = nullptr;
    for (std::vector<UIElement*> s : allUIElements) {
        for (UIElement* e : s) {
            e->update();
            if (!mouseOverElement && e->tangible) {
                int x, y;
                getMouseWorldCoordinates(x, y);
                if (pointWithin(x, y, e->positionX, e->positionY, e->width, e->height)) {
                    mouseOverElement = e;
                }
            }
        }
    }

    //Call mouse over functions
    if (mouseOverElement != nullptr) {
        if (getKeyDown(MOUSE_LEFT) || getKeyDown(MOUSE_RIGHT)) {
            setSelected(mouseOverElement);
        }
        if (mouseOverElement != lastMouseOverElement && lastMouseOverElement != nullptr) {
            lastMouseOverElement->onMouseExit();
        }
        //Check if mouse over element was deleted in setSeleceted() or onMouseLeft()
        if (mouseOverElement) {
            if (mouseOverElement != lastMouseOverElement)
                mouseOverElement->onMouseEnter();
            mouseOverElement->onMouseOver();
            lastMouseOverElement = mouseOverElement;
        }
    }
}

void UIElement::renderUIElements()
{
    for (std::vector<std::vector<UIElement*>>::reverse_iterator i = allUIElements.rbegin();
        i != allUIElements.rend(); ++i) {
        for (std::vector<UIElement*>::reverse_iterator j = (*i).rbegin();
            j != (*i).rend(); ++j) {
            if ((*j)->visible) 
                (*j)->render();
        }
    }
}

inline void UIElement::setSelected(UIElement * element)
{
    if (selectedElement != nullptr && selectedElement != element)
        selectedElement->onDeselect();
    selectedElement = element;
    selectedElement->onSelect();
    UIActionListener::notifyAll();
}

void UIElement::render()
{
}

void UIElement::onMouseEnter()
{
}

void UIElement::onMouseOver()
{
}

void UIElement::onMouseExit()
{
}

void UIElement::onSelect()
{
}

void UIElement::onDeselect()
{
}

void UIElement::update()
{
}

void UIElement::getAlignmentOffset(Alignment align, int _width, int _height, int & alignx, int & aligny) const
{
    switch (align) {
    case ALIGN_UP:
        alignx = (width / 2) - (_width / 2);
        aligny = 0;
        break;
    case ALIGN_DOWN:
        alignx = (width / 2) - (_width / 2);
        aligny = height - _height;
        break;
    case ALIGN_LEFT:
        alignx = 0;
        aligny = (height / 2) - (_height / 2);
        break;
    case ALIGN_RIGHT:
        alignx = width - _width;
        aligny = (height / 2) - (_height / 2);
        break;
    case ALIGN_CENTER:
        alignx = (width / 2) - (_width / 2);
        aligny = (height / 2) - (_height / 2);
        break;
    case ALIGN_UPPER_LEFT:
        alignx = 0;
        aligny = 0;
        break;
    case ALIGN_UPPER_RIGHT:
        alignx = width - _width;
        aligny = 0;
        break;
    case ALIGN_LOWER_LEFT:
        alignx = 0;
        aligny = height - _height;
        break;
    case ALIGN_LOWER_RIGHT:
        alignx = width - _width;
        aligny = height - _height;
        break;
    case ALIGN_NONE:
        alignx = 0;
        aligny = 0;
        break;
    }
}

void UIElement::drawSquare(int _width, int _height, Color color, Fill_Type type, Alignment align, int offsetX, int offsetY) const
{
    int alignX, alignY = 0;
    getAlignmentOffset(align, _width, _height, alignX, alignY);
    SDL_Rect rect = { positionX + alignX + offsetX, positionY + alignY + offsetY, _width, _height };
    SDL_SetRenderDrawColor(GraphicsEngine::getActiveRenderer(), color.r, color.g, color.b, color.a);
    switch (type)
    {
    case SOLID:
        SDL_RenderFillRect(GraphicsEngine::getActiveRenderer(), &rect);
        break;
    case OUTLINE:
        SDL_RenderDrawRect(GraphicsEngine::getActiveRenderer(), &rect);
        break;
    default:
        break;
    }
}

//Courtesy of https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
//Slightly modified
void UIElement::drawCircle(int diameter, Color color, Fill_Type type , Alignment align, int offsetX, int offsetY) const
{

    int radius = diameter / 2;
    for (int r = (type == SOLID ? 1 : radius); r <= radius; r++) {
        int alignX, alignY = 0;
        getAlignmentOffset(align, diameter, diameter, alignX, alignY);
        SDL_SetRenderDrawColor(GraphicsEngine::getActiveRenderer(), color.r, color.g, color.b, color.a);

        int32_t x = r - 1;
        int32_t y = 0;
        int32_t tx = 1;
        int32_t ty = 1;
        int32_t err = tx - (r << 1); // shifting bits left by 1 effectively
                                      // doubles the value. == tx - diameter

        /*TODO: add logic for fill type*/

        while (x >= y)
        {
            //  Each of the following renders an octant of the circle
            SDL_RenderDrawPoint(GraphicsEngine::getActiveRenderer(), radius + positionX + alignX + offsetX + x, radius + positionY + alignY + offsetY - y);
            SDL_RenderDrawPoint(GraphicsEngine::getActiveRenderer(), radius + positionX + alignX + offsetX + x, radius + positionY + alignY + offsetY + y);
            SDL_RenderDrawPoint(GraphicsEngine::getActiveRenderer(), radius + positionX + alignX + offsetX - x, radius + positionY + alignY + offsetY - y);
            SDL_RenderDrawPoint(GraphicsEngine::getActiveRenderer(), radius + positionX + alignX + offsetX - x, radius + positionY + alignY + offsetY + y);
            SDL_RenderDrawPoint(GraphicsEngine::getActiveRenderer(), radius + positionX + alignX + offsetX + y, radius + positionY + alignY + offsetY - x);
            SDL_RenderDrawPoint(GraphicsEngine::getActiveRenderer(), radius + positionX + alignX + offsetX + y, radius + positionY + alignY + offsetY + x);
            SDL_RenderDrawPoint(GraphicsEngine::getActiveRenderer(), radius + positionX + alignX + offsetX - y, radius + positionY + alignY + offsetY - x);
            SDL_RenderDrawPoint(GraphicsEngine::getActiveRenderer(), radius + positionX + alignX + offsetX - y, radius + positionY + alignY + offsetY + x);

            if (err <= 0)
            {
                y++;
                err += ty;
                ty += 2;
            }
            if (err >= 0)
            {
                x--;
                tx += 2;
                err += tx - (radius << 1);
            }
        }
    }
}

void UIElement::renderText(std::string text, Color color, Alignment align, int offsetX, int offsetY) const
{
    int alignx, aligny = 0;
    getAlignmentOffset(align, text.length() * 4, 8, alignx, aligny);

    TextureManager::fontTextures[0].renderText(positionX + alignx + offsetX, positionY + aligny + offsetY, text, color);
}

void UIElement::renderTextBackdrop(std::string text, Color color, Alignment align, int offsetX, int offsetY, Color backColor) const
{
    renderText(text, backColor, align, offsetX + 1, offsetY + 1);
    renderText(text, color, align, offsetX, offsetY);
}

void UIElement::moveToFrontOffLayer(unsigned int l)
{
    vector<UIElement*>::iterator it = allUIElements[layer].begin();

    while (it != allUIElements[layer].end()) {

        if (*it == this) {

            it = allUIElements[layer].erase(it);
            break;
        }
        else ++it;
    }
    layer = l;
    allUIElements[layer].insert(allUIElements[layer].begin(), this);
}

