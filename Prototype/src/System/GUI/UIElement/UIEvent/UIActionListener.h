#pragma once
#include "UIEvent.h"
#include "..\UIElement.h"
#include <set>

class UIActionListener {
public:
    UIActionListener();
    virtual ~UIActionListener();

    //Called when a button that is being listened on is pressed
    virtual void actionPerformed(UIEvent* e);

    //Not functional, because UIWindow class does not yet exist
    virtual void windowOpened(UIEvent* e);
    virtual void windowActivated(UIEvent* e);
    virtual void windowDeactivated(UIEvent* e);
    virtual void windowClosed(UIEvent* e);
    //Called when selected UIElement is changed
    virtual void onNotify();

protected:

private:

    static std::set<UIActionListener*> allListeners;
    //Calls onNotify in all action listeners
    static void notifyAll();
    friend class UIElement;
};