#pragma once
#include "UIPanel.h"

class UIGridEditor;
class UIInfoBox : public UIPanel {
public:
    UIInfoBox(UIGridEditor* _selector,  int _positionX, int _positionY, int _width, int _height,
        int _layer, std::string _label);
private:
    UIGridEditor* selector;
    
    void render();
};