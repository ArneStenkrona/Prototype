#pragma once
#include "UIMovable.h"
#include "UIButton.h"
#include "UITextBox.h"
#include <string>

class UIPromptListener;
class UIPrompt : public UIMovable {
public:
    UIPrompt(UIPromptListener* _listener, int _positionX, int _positionY, int _width, int _height,
        int _layer, std::string _label);

    std::string getInput();

private:
    const UIPromptListener* listener;

    //Textbox containing input
    UITextBox* textBox;
    //label of prompt
    std::string label;

    void render();
    void derivedUpdate();

    class OkListener : public UIActionListener {
        public:
            OkListener(UIPromptListener * _pl) :
                pl(_pl) {}

            void actionPerformed(UIEvent* e);
        private:
            UIPromptListener* pl;
    };

    class CancelListener : public UIActionListener {
        public:
            CancelListener(UIPromptListener * _pl) :
                pl(_pl) {}

            void actionPerformed(UIEvent* e);
        private:
            UIPromptListener* pl;
    };

};

//Attach to button to instantiate a prompt on buttonpress 
class UIPromptListener : public UIActionListener {
public:
    UIPromptListener(std::string _label);

    //Closes prompt
    void cancel();
    //Closes prompt and retrieves input
    virtual void ok();

    void actionPerformed(UIEvent* e);
protected:
    UIPrompt* prompt;
    //Label of the prompt
    std::string label;
    //Input from the prompt
    std::string input;
};