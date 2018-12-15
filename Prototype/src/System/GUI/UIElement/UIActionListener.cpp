#include "UIActionListener.h"

std::set<UIActionListener*> UIActionListener::allListeners = std::set<UIActionListener*>();

UIActionListener::UIActionListener()
{
    allListeners.insert(this);
}

UIActionListener::~UIActionListener()
{
    allListeners.erase(this);
}

void UIActionListener::actionPerformed(UIEvent * e)
{
}

void UIActionListener::windowOpened(UIEvent * e)
{
}

void UIActionListener::windowActivated(UIEvent * e)
{
}

void UIActionListener::windowDeactivated(UIEvent * e)
{
}

void UIActionListener::windowClosed(UIEvent * e)
{
}

void UIActionListener::onNotify()
{
}

void UIActionListener::notifyAll()
{
    for (UIActionListener* listener : allListeners) {
        listener->onNotify();
    }
}
