#pragma once
#include "UIComponent.h"
#include <string>

class UITextBox : public UIComponent {
public:
    UITextBox(int _positionX, int _positionY, int _length, int _layer, UIActionListener* _listener = nullptr);

    inline std::string getInput() const { return input; }
private:
    //Input of the textbox
    std::string input;

    void render();
    void update();
};