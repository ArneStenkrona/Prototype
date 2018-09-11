#pragma once
#include "GameObject\Component\component.h"
#include "GameObject/Component/geometry/position.h"
#include "GameObject/Component/geometry/velocity.h"
#include "GameObject\Component\geometry\rotation.h"
#include "GameObject/Component/graphics/sprite.h"
#include "GameObject\Component\graphics\animator.h"
#include "../graphics/spriteRenderer.h"

class Splash : public Component {
public:
    Splash(GameObject *_object);
    void start();
    void onActivate();
    void update();
    void updateComponents();

    void setClip(AnimationClip clip);
private:
    Position * position;
    Velocity* velocity;
    Sprite* sprite;
    Animator* animator;
    Rotation* rotation;
    SpriteRenderer* renderer;

    string clipName;

    bool woke = false;
};