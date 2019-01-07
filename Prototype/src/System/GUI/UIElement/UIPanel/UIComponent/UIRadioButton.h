#pragma once
#include "UIButtonBase.h"
/*UNFINISHED IMPLEMENTATION OF A RADIO BUTTON*/
class UIRadioButton;
class RadioButtonGroup {
public:

private:
    std::vector<UIRadioButton*> buttons;
};

class UIRadioButton : public UIButtonBase {
public:
    //Creates an instance of UIButton with listener _listener.
    //The listener is destroyed when UIButton is destroyed
    UIRadioButton(UIActionListener* _listener, int _positionX, int _positionY, unsigned int _diameter,
        int _layer, std::string _text);
    virtual ~UIRadioButton();

    void addToGroup(RadioButtonGroup* _group);

protected:

private:
    //void onMouseOver();
    //void update();
    void render();

    //The state of the button
    bool isChecked;
    //Group that the button belongs to
    //Only one radio button per group may be checked
    RadioButtonGroup* group;
};