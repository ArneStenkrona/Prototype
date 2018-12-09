#pragma once
#include "GameObject/Component/component.h"
#include "GameObject/Component/geometry/position.h"
#include "GameObject/Component/geometry/velocity.h"
#include "GameObject/Component/graphics/sprite.h"
#include "GameObject\Component\graphics\animator.h"
#include "GameObject\Component\graphics\spriteRenderer.h"
#include "weapon.h"

class GameObject;
class Movement : public Component {
public:
    Movement(GameObject *_object);
    void start();
    void update();
    void updateComponents();
    void onCollisionEnter(Collision *collision);
    void onColliding(Collision *collision);
    void onCollisionExit();

    //Maximum speed (compares to velocity.magnitude())
    double speed = 15;
    //acceleration factor [0,inf[
    double acceleration = 1.5;
    //Drag factor [0,1]
    double drag = 0.8;

private:
    Position *position;
    Velocity *velocity;
    Sprite *sprite;
    Animator *animator;

    //states for state machine
    //this behaviour should be delegated to an animation data-structure
    int state;
    int prevState;
    int transitionCounter;
    enum state {
        nullState,
        idle,
        running,
        falling,
        states
    };

    bool grounded;

};