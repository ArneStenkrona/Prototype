#pragma once
#include "UIMovable.h"
#include <string>

class UIPrompt : public UIMovable {
public:
    UIPrompt(int _positionX, int _positionY, int _width, int _height,
        int _layer, std::string _question);

private:
    std::string question;
    std::string userInput;

    void render();
    void derivedUpdate();
};