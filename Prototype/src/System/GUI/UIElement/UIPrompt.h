#pragma once
#include <string>

class Prompt {
public:
    Prompt(int _positionX, int _positionY, int _width, int _height,
            std::string _question);

private:
    std::string question;
    std::string userInput;

    int positionX, positionY;
    int width, height;
};