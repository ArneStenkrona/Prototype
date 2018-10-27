#include "UIPanel.h"
#include "System\IO\inputManager.h"

UIPanel::UIPanel(int _positionX, int _positionY, int _width, int _height, int _layer)
    :UIElement(_positionX, _positionY, _width, _height, _layer, true)
{
}

UIPanel::~UIPanel()
{
    for (UIComponent* c : attached) {
        delete (c);
    }
}

void UIPanel::attach(UIComponent * c, Alignment a, int offsetX, int offsetY)
{
    c->moveToFrontOffLayer(layer);
    int ax, ay = 0;
    getAlignmentOffset(a, c->width, c->height, ax, ay);
    c->positionX = positionX + offsetX + ax;
    c->positionY = positionY + offsetY + ay;
    attached.push_back(c);

    c->panel = this;
}

bool UIPanel::isSelected() const
{
    if (UIElement::isSelected()) return true;
    for (UIElement* e : attached) {
        if (e->isSelected())
            return true;
    }
    return false;
}

void UIPanel::toggleSelected()
{
    if (attached.empty()) return;
    int index = 0;
    for (int i = 0; i < attached.size(); i++) {
        if (attached[i] == UIElement::getSelected()) {
            index = i + 1;
            index = index % attached.size();
            break;
        }
    }
    UIElement::setSelected(attached[index]);
}

void UIPanel::update()
{
    if (isSelected() && getKeyDown(INPUT_KEY_TAB))
        toggleSelected();
}
