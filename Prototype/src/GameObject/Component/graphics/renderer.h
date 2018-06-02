#pragma once
#include "../component.h"
#include "SDL_image.h"
#include "../geometry/position.h"
#include "sprite.h"
#include "camera.h"

class GameObject;

class Renderer : public Component {
public:
    Renderer(GameObject *_object);
    void start();
    void update();
    void updateComponents();

    static void setCamera(GameObject *_camera);

    static GameObject *mainCamera;

    static Point getCameraPosition();

    void setTileIndex(int index);

private:
    static Position *cameraPosition;

    SDL_Renderer *renderer;
    Sprite *sprite;
    Position *position;

    //Index on the tile sheet of the tile
    //Set to -1 if no tileIndex
    //int tileIndex;
};
