#pragma once
#include "../component.h"
#include "SDL_image.h"
#include "../geometry/position.h"
#include "sprite.h"
#include "camera.h"
#include "GameObject\Component\geometry\rotation.h"

class GameObject;

class Renderer : public Component {
public:
    Renderer(GameObject *_object);

    ~Renderer();

    void start();
    void update();
    void updateComponents();

    void setRenderLayer(int layer);

    static void setCamera(GameObject *_camera);

    static GameObject *mainCamera;

    static Point getCameraPosition();

    void render();

private:
    static Position *cameraPosition;

    int renderLayer;

    SDL_Renderer *renderer;
    Sprite *sprite;
    Position *position;
    Rotation *rotation;
};
