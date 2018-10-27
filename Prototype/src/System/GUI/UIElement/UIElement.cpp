#include "UIElement.h"
#include "System\IO\inputManager.h"
#include "System\graphics\graphicsEngine.h"
#include <iostream>

std::vector<std::vector<UIElement*>> UIElement::allUIElements = std::vector<std::vector<UIElement*>>();
UIElement* UIElement::selectedElement = nullptr;
unsigned int UIElement::NumberOfElements = 0;

UIElement::UIElement(int _posx, int _posy, int _width, int _height, 
                    int _layer, bool _tangible, bool _visible)
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
    if (selectedElement == this)
        selectedElement = nullptr;

    vector<UIElement*>::iterator it = allUIElements[layer].begin();

    while (it != allUIElements[layer].end()) {

        if (*it == this) {

            it = allUIElements[layer].erase(it);
            break;
        }
        else ++it;
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
    UIElement* mouseOverElement = nullptr;
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
    if (mouseOverElement != nullptr) {
        if (getKeyDown(MOUSE_LEFT) || getKeyDown(MOUSE_RIGHT)) {
            setSelected(mouseOverElement);
        }
        mouseOverElement->onMouseOver();
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
}

void UIElement::render()
{
}

void UIElement::onMouseOver()
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

void UIElement::drawSquare(int _width, int _height, Color color, Square_type type, Alignment align, int offsetX, int offsetY) const
{
    int alignx, aligny = 0;
    getAlignmentOffset(align, _width, _height, alignx, aligny);
    SDL_Rect rect = { positionX + alignx + offsetX, positionY + aligny + offsetY, _width, _height };
    SDL_SetRenderDrawColor(GraphicsEngine::getActiveRenderer(), color.r, color.g, color.b, color.a);
    switch (type)
    {
    case SOLID_SQUARE:
        SDL_RenderFillRect(GraphicsEngine::getActiveRenderer(), &rect);
        break;
    case OUTLINE_SQUARE:
        SDL_RenderDrawRect(GraphicsEngine::getActiveRenderer(), &rect);
        break;
    default:
        break;
    }
}

void UIElement::renderText(std::string text, Color color, Alignment align, int offsetX, int offsetY) const
{
    int alignx, aligny = 0;
    getAlignmentOffset(align, text.length() * 4, 8, alignx, aligny);

    TextureManager::fontTextures[0].renderText(positionX + alignx + offsetX, positionY + aligny + offsetY, text, color);
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

