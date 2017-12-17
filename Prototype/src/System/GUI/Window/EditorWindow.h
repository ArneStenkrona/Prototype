#pragma once
#include "lwindow.h"

/*
    This class represents the main viewport in editing mode.
    It is a mess right now, not unlike a lot of my code.
*/

class EditorWindow : public LWindow {
public:
    EditorWindow(int _screen_width, int _screen_height,
        int _scale_x, int _scale_y);

    void update();
private:
    static const int gridSize;
    void drawSquare(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    //position relative to origin
    int posX;
    int posY;
    //updates relevant input for editor window
    void updateInput();

    //Snaps coordinate to nearest vertex
    int snapToGrid(int i);

    //Sets input to closest vertex
    void getClosestVertex(int &x, int &y);
};