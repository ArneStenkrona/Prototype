#include "UIPrompt.h"
#include "System\IO\inputManager.h"
UIPrompt::UIPrompt(int _positionX, int _positionY, int _width, int _height, int _layer, std::string _question)
        :UIMovable(_positionX, _positionY, _width, _height, _layer), question(_question)
{
}

void UIPrompt::render()
{
    UIElement::drawSquare(width, height, {0,0,0,255});
    UIElement::drawSquare(width -8 , 8, { 50,50,50,255 }, SOLID_SQUARE, ALIGN_CENTER);
    UIElement::renderText(question, { 255,255,255,255 }, ALIGN_UP, 0, 2);
    //Start of rendered string
    int start = userInput.length() - (width - 10) / 4;
    start = start < 0 ? 0 : start;
    std::string rText = userInput.substr(start, userInput.length());
    UIElement::renderText(rText, { 255,255,255,255 }, ALIGN_LEFT, 5);

}

void UIPrompt::derivedUpdate()
{
    modifyStringFromInput(userInput);
}
