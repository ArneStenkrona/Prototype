#include "debug_scene0.h"
#include "GameObject\Component\gameplay\weapon.h"
#include "GameObject/Component/graphics/camera.h"
#include "GameObject/Component/graphics/spriteRenderer.h"
#include "GameObject/Component/graphics/sprite.h"
#include "GameObject/Component/gameplay/movement.h"
#include "GameObject/Component/geometry/polygonCollider.h"
#include "GameObject/Component/geometry/position.h"
#include "GameObject/Component/geometry/velocity.h"
#include "GameObject\Prefabrications\prefabrications.h"
#include "GameObject\objectPool.h"
#include <iostream>

Debug_scene0::Debug_scene0() : Scene()
{
}

Debug_scene0::~Debug_scene0()
{
}

void Debug_scene0::setUpScene()
{
    Scene::setUpScene();

    GameObject *c = Character().instantiate();

    GameObject *weapon = new GameObject();
    weapon->addComponent<Weapon>()->setOwner(c);

    GameObject *camera = new GameObject();
    camera->addComponent<Camera>()->setTarget(c);
    SpriteRenderer::setCamera(camera);

    GameObject* container = GlassContainer().instantiate();
    container->getComponent<Position>()->position = Point(7 * 32, 4 * 32);

    ObjectPool::addToPool(new MuzzleFlash(), 10);
    ObjectPool::addToPool(new Shrapnel(), 10);
    ObjectPool::addToPool(new LaserBeam(), 10);
}

