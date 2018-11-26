#include "UIPrompt.h"
#include "UIActionListener.h"
#include "System\IO\inputManager.h"

class OkListener : public UIActionListener {

};

class CancelListener : public UIActionListener {
public:
    CancelListener(UIPromptListener * _pl) :
    pl(_pl) {}

    void actionPerformed(UIEvent* e) {
        pl->cancel();
    }
private:
    UIPromptListener* pl;
};


UIPrompt::UIPrompt(UIPromptListener * _listener, int _positionX, int _positionY, int _width, int _height, int _layer, std::string _label)
    :UIMovable(_positionX, _positionY, _width, _height, _layer), 
     label(_label), textBox(new UITextBox(0, 0, width - 8, _layer)),
     listener(_listener)
{
    attach(new UIButton(new OkListener(), 50, 50, 40, 20, 0, "OK"), ALIGN_DOWN, -30, -5);
    attach(new UIButton(new CancelListener(_listener), 50, 50, 40, 20, 0, "Cancel"), ALIGN_DOWN, 30, -5);

    attach(textBox, ALIGN_UP, 0, 20);
    UIElement::setSelected(this);
}

UIPrompt::~UIPrompt()
{
}

std::string UIPrompt::getInput()
{
    return textBox->getInput();
}

void UIPrompt::render()
{
    UIElement::drawSquare(width, height, {0,0,0,255});
    UIElement::renderText(label, { 255,255,255,255 }, ALIGN_UP, 0, 2);

    if (isSelected())
        UIElement::drawSquare(width, height, { 66, 134, 244, 255 }, OUTLINE_SQUARE);
}

void UIPrompt::derivedUpdate()
{
}

UIPromptListener::UIPromptListener(std::string _label)
    : label(_label)
{
}

void UIPromptListener::cancel()
{
    delete (prompt);
    prompt = NULL;
}

void UIPromptListener::ok()
{
    input = prompt->getInput();
    delete (prompt);
}

void UIPromptListener::actionPerformed(UIEvent * e)
{
    if (prompt)
        UIElement::setSelected(prompt);
    else {
        prompt = new UIPrompt(this, 50, 50, 150, 70, 0, label);
    }
}
