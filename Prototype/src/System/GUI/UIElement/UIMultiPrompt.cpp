#include "UIMultiPrompt.h"
#include "UIActionListener.h"

UIMultiPrompt::UIMultiPrompt(UIMultiPromptListener* _listener, int _positionX, int _positionY, int _width,
    int _layer, std::string _label, std::vector<std::string> _labels)
    : UIMovable(_positionX, _positionY, _width, _labels.size() * 32 + 45, _layer),
    label(_label), labels(_labels),
    listener(_listener)
{
    for (unsigned int i = 0; i < labels.size(); i++) {
        textBoxes.push_back(new UITextBox(0, 0, width - 8, _layer));
    }

    for (unsigned int i = 0; i < textBoxes.size(); i++) {
        attach(textBoxes[i], ALIGN_UP, 0, 32 * i + 28);
    }

    attach(new UIButton(new OkListener(_listener), 50, 50, 40, 20, 0, "OK"), ALIGN_DOWN, -30, -5);
    attach(new UIButton(new CancelListener(_listener), 50, 50, 40, 20, 0, "Cancel"), ALIGN_DOWN, 30, -5);
}

std::vector<std::string> UIMultiPrompt::getInput()
{
    std::vector<std::string> vec = {};

    for (UITextBox* b : textBoxes) {
        vec.push_back(b->getInput());
    }

    return vec;
}

void UIMultiPrompt::render()
{
    UIElement::drawSquare(width, height, { 0,0,0,255 });
    UIElement::renderText(label, { 255,255,255,255 }, ALIGN_UP, 0, 2);

    for (unsigned int i = 0; i < labels.size(); i++) {
        UIElement::renderText(labels[i] + ": ", { 255,255,255,255 }, ALIGN_UPPER_LEFT, 5, 16 + i * 32);
    }

    if (isSelected())
        UIElement::drawSquare(width, height, { 66, 134, 244, 255 }, OUTLINE);
}

void UIMultiPrompt::derivedUpdate()
{
}

UIMultiPromptListener::UIMultiPromptListener(std::string _label, std::vector<std::string> _labels)
    : label(_label), labels(_labels)
{
}

void UIMultiPromptListener::cancel()
{
    delete (prompt);
    prompt = NULL;
}

void UIMultiPromptListener::ok()
{
    input = prompt->getInput();
    delete (prompt);
    prompt = NULL;
}

void UIMultiPromptListener::actionPerformed(UIEvent*)
{
    if (prompt)
        UIElement::setSelected(prompt);
    else {
        prompt = new UIMultiPrompt(this, 50, 50, 150, 0, label, labels);
    }
}

void UIMultiPrompt::OkListener::actionPerformed(UIEvent*) {
    pl->ok();
}

void UIMultiPrompt::CancelListener::actionPerformed(UIEvent*) {
    pl->cancel();
}