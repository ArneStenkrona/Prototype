#pragma once
#include "UIMovable.h"
#include "..\UIComponent\UITextBox.h"
#include "..\..\UIEvent\UIActionListener.h"
#include <string>
#include <vector>
#include <tuple>

//Listens for input from input methods
//Input methods may send an event containing the input as a message
class UIinputListener : public UIActionListener {
public:
    UIinputListener() {}
    ~UIinputListener() {}
    std::string getInput() {
        return input;
    }
    void actionPerformed(UIEvent* e) {
        input = e->getMessage();
    }

private:
    std::string input;
};

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

    //Provides access to user input through listeners
    std::vector<UIinputListener*> inputs;

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