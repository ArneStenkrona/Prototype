#pragma once
#include "GameObject\Component\graphics\renderer.h"
#include "SDL_image.h"
#include <vector>
#include <set>
#include "System\GUI\Window\lwindow.h"
#include "System\GUI\Window\EditorWindow.h"

class GraphicsEngine {
public:
    static bool initializeGraphicsEngine();
    static void closeGraphicsEngine();

    static LWindow* createGameWindow();
    static EditorWindow* createEditorWindow();

    //Renderers will render layer by layer
    static void addToRenderQueue(Renderer *r, int layer);
    static void removeFromRenderQueue(Renderer *r, int layer);

    static SDL_Renderer* getActiveRenderer();
    static LWindow* getActiveWindow() { return activeWindow; }

    //Screen dimension constants
    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT;
    static const float SCALE_X;
    static const float SCALE_Y;

    //Frame rate related
    static const int SCREEN_FPS;
    static const int SCREEN_TICK_PER_FRAME;
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
    /* Sets version and parameters for openGL
    OBSERVE: This does not yet call glewInit()
    as a context may not have yet been created*/
    static const bool initOpenGL();

    static void experimentGL();

    static LTexture frameBuffer;
};
