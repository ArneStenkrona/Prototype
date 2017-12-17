#include "editor.h"
#include "System/IO/inputManager.h"

Editor::Editor()
{
    editorWindow = new EditorWindow(2*512,2*288,2,2);
}

Editor::~Editor()
{
    delete(editorWindow);
}

void Editor::run()
{
    while (!editorWindow->hasExited()) {
        LWindow::updateAll();
        //updateInputManager();
    }
}
