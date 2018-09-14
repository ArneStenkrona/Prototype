#pragma once
#pragma once
#include "GameObject\Component\component.h"
#include "GameObject/Component/geometry/position.h"
#include "GameObject/Component/geometry/velocity.h"
#include "GameObject\Component\geometry\rotation.h"
#include "GameObject/Component/graphics/sprite.h"
#include "GameObject\Component\graphics\animator.h"
#include "GameObject\Component\geometry\polygonCollider.h"
#include "../../graphics/spriteRenderer.h"

class GameObject;
class Container : public Component {
public:
    Container(GameObject *_object);
    void updateComponents();

    void update();

    void rayHit(RayCastHit* hit);

private:
    Position * position;
    Sprite* sprite;
    Rotation* rotation;
    SpriteRenderer* renderer;
    PolygonCollider* collider;
};