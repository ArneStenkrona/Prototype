#pragma once
#include "UISelector.h"
#include "UISelectable.h"
#include <map>

class UIToolSelector : public UISelector {

public:
    UIToolSelector(int _posx, int _posy, int _layer,
        Color _selectedColor = COLOR_GREEN, Color _hoverColor = COLOR_CYAN);


    enum TOOL {
        PLACE_TOOL,
        DELETE_TOOL,
        TOTAL_TOOLS
    };

    static std::string getToolString(TOOL t) { return toolDictionary.at(t); }

private:
    static const std::map<TOOL, std::string> toolDictionary;
    void update();
    void render();

    friend class UISelectable;
};
