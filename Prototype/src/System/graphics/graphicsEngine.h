#pragma once
#include "GameObject\Component\graphics\renderer.h"
#include "SDL_image.h"
#include <vector>
#include <set>
#include "System\GUI\Window\lwindow.h"
#include "System\GUI\Window\EditorWindow.h"

//Oversees the graphics
class GraphicsEngine {
public:
    static bool initializeGraphicsEngine();
    static void closeGraphicsEngine();

    static LWindow* createGameWindow();
    static EditorWindow* createEditorWindow(Editor *editor);

    //Renderers will render layer by layer
    static void addToRenderQueue(Renderer *r, unsigned int layer);
    static void removeFromRenderQueue(Renderer *r, unsigned int layer);

    static SDL_Renderer* getActiveRenderer();
    inline static LWindow* getActiveWindow() { return activeWindow; }

    //Screen dimension constants
    //How much is pixel is scaled
    static const float SCALE_X;
    static const float SCALE_Y;
    //Dimensions measured in in-game pixels, i.e. dimensions divided by scale
    static const int LOGICAL_WIDTH;
    static const int LOGICAL_HEIGHT;
    //Dimensions measured in physical screen pixels.
    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT;

    //Frame rate related
    static const int SCREEN_FPS;
    static const int MICROSECONDS_PER_FRAME;
    //Clears gameWindow
    static void clearWindow();

    //Renders each layer one by one, 0 is rendered last
    static void renderGraphics();

private:
    static vector<set<Renderer*>> renderQueue;
    //Main renderer in game. 
    static SDL_Renderer* activeRenderer;
    //Main window for the game
    static LWindow* activeWindow;

    static const bool initSDL();

    static LTexture frameBuffer;
};
