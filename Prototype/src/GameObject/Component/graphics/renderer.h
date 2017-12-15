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

    //Sets quad to render from tilesheet
    void setTileQuad(SDL_Rect *_quad);

private:
    static Position *cameraPosition;

    SDL_Renderer *renderer;
    Sprite *sprite;
    Position *position;
                    //If the sprite is from a sheet this should be set to the appopriate sprite
                    //If this is null, the rendered quad will take the whole texture
    SDL_Rect *tileQuad;
};
