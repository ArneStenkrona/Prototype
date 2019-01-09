#include "UIInfoBox.h"
#include "..\..\UIGridEditor.h"
#include "..\..\UISelect\UISelector\UISelector.h"

UIInfoBox::UIInfoBox(UIGridEditor* _selector, int _positionX, int _positionY, int _width, int _height, int _layer, std::string _label)
    :UIPanel(_positionX, _positionY, _width, _height, _layer), selector(_selector)
{
}

void UIInfoBox::render()
{
    drawSquare(width, height, COLOR_BLACK);

    int cordX, cordY = 0;
    selector->getActiveTileCoordinates(cordX, cordY);
    const std::string sx = cordX == -1 ? "N/A" : to_string(cordX);
    const std::string sy = cordY == -1 ? "N/A" : to_string(cordY);
    const std::string coordinates = "X: " + sx + " - Y: " + sy;

    const std::string tool = "MODE: " + UIToolSelector::getToolString(selector->getTool());

    const std::string activeSelector = "Active Selector: " + UISelector::getActiveSelector()->getLabel();

    int rot;
    bool flipH, flipV;
    UISelector::getActiveSelector()->getRotationAndFlip(rot, flipH, flipV);

    const std::string rotation = "Rotation: " + to_string(90 * rot) + " degrees";
    std::string flip = "No flip";
    if (flipH && flipV) flip = "Horizontal and vertical flip";
    else if (flipH) flip = "Horizontal flip";
    else if (flipV) flip = "Vertical flip";

    renderTextBackdrop(coordinates, { 255,255,255,255 }, ALIGN_UPPER_LEFT, 4, 4, COLOR_DARK_GREY);
    renderTextBackdrop(tool, { 255,255,255,255 }, ALIGN_UPPER_LEFT, 4, 4 + 12, COLOR_DARK_GREY);
    renderTextBackdrop(activeSelector, { 255,255,255,255 }, ALIGN_UPPER_LEFT, 4, 4 + 24, COLOR_DARK_GREY);
    renderTextBackdrop(rotation, { 255,255,255,255 }, ALIGN_UPPER_LEFT, 4, 4 + 36, COLOR_DARK_GREY);
    renderTextBackdrop(flip, { 255,255,255,255 }, ALIGN_UPPER_LEFT, 4, 4 + 48, COLOR_DARK_GREY);

}
