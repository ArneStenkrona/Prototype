#pragma once
#include "UIPanel.h"

class UIGridSelector;
class UIInfoBox : public UIPanel {
public:
    UIInfoBox(UIGridSelector* _selector,  int _positionX, int _positionY, int _width, int _height,
        int _layer, std::string _label);
private:
    UIGridSelector* selector;
    
    void render();
};