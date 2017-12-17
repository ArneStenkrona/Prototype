#pragma once
#include "System\GUI\Window\EditorWindow.h"
class Editor {
public:
    Editor();
    ~Editor();

    void run();
private:
    EditorWindow *editorWindow;
};