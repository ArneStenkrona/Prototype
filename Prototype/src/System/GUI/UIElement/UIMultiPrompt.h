#pragma once
#include "UIMovable.h"
#include "UIButton.h"
#include "UITextBox.h"
#include <string>
#include <vector>

class UIMultiPromptListener;
class UIMultiPrompt : public UIMovable {
public:
    UIMultiPrompt(UIMultiPromptListener* _listener, int _positionX, int _positionY, int _width,
        int _layer, std::string _label, std::vector<std::string> _labels);
    std::vector<std::string> getInput();
private:
    UIMultiPromptListener* listener;

    //label of prompt
    std::string label;
    //label of textfields
    std::vector<std::string> labels;
    //Textbox containing input
    std::vector<UITextBox*> textBoxes;

    void render();
    void derivedUpdate();

    class OkListener : public UIActionListener {
    public:
        OkListener(UIMultiPromptListener * _pl) :
            pl(_pl) {}

        void actionPerformed(UIEvent* e);
    private:
        UIMultiPromptListener* pl;
    };

    class CancelListener : public UIActionListener {
    public:
        CancelListener(UIMultiPromptListener * _pl) :
            pl(_pl) {}

        void actionPerformed(UIEvent* e);
    private:
        UIMultiPromptListener* pl;
    };

};

//Attach to button to instantiate a prompt on buttonpress 
class UIMultiPromptListener : public UIActionListener {
public:
    UIMultiPromptListener(std::string _label, std::vector<std::string> _labels);

    //Closes prompt
    void cancel();
    //Closes prompt and retrieves input
    virtual void ok();

    void actionPerformed(UIEvent* e);

protected:
    UIMultiPrompt* prompt;
    //Label of the prompt
    std::string label;
    //label of textfields
    std::vector<std::string> labels;
    //Input from the prompt
    std::vector<std::string> input;
};