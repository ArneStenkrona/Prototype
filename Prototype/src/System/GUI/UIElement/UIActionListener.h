#pragma once
#include "UIEvent.h"

class UIActionListener {
public:
    UIActionListener();
    ~UIActionListener();

    //Called when a button that is being listened on is pressed
    virtual void actionPerformed(UIEvent* e);

    //Not functional, because UIWindow class does not yet exist
    virtual void windowOpened(UIEvent* e);
    virtual void windowActivated(UIEvent* e);
    virtual void windowDeactivated(UIEvent* e);
    virtual void windowClosed(UIEvent* e);
protected:

};