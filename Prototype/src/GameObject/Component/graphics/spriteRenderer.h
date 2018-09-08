#pragma once
#include "../component.h"
#include "SDL_image.h"
#include "../geometry/position.h"
#include "sprite.h"
#include "GameObject\Component\geometry\rotation.h"
#include "renderer.h"

class GameObject;
class SpriteRenderer : public Renderer {
public:
    SpriteRenderer(GameObject *_object);

    void updateComponents();

    static GameObject *mainCamera;

    void render();

private:
    Sprite *sprite;
    Position *position;
    Rotation *rotation;
};
