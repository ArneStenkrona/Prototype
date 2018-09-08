#pragma once
#include "GameObject\Component\component.h"
#include "GameObject/gameObject.h"
#include "GameObject/Component/geometry/position.h"
#include "GameObject/Component/geometry/velocity.h"
#include "GameObject\Component\geometry\rotation.h"
#include "GameObject/Component/graphics/sprite.h"
#include "GameObject\Component\graphics\animator.h"
#include "../graphics/renderer.h"

class GameObject;
class Weapon : public Component {
public:
    Weapon(GameObject *_object);
    void start();
    void update();
    void updateComponents();

    void setOwner(GameObject* owner);

private:
    Position* position;
    Velocity* velocity;
    Sprite* sprite;
    Animator* animator;
    Rotation* rotation;
    Renderer* renderer;

    Position* ownerPosition;
};