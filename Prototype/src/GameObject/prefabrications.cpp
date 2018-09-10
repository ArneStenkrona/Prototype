#include "prefabrications.h"
#include "GameObject\Component\gameplay\weapon.h"
#include "GameObject/Component/graphics/camera.h"
#include "GameObject/Component/graphics/spriteRenderer.h"
#include "GameObject/Component/graphics/sprite.h"
#include "GameObject/Component/gameplay/movement.h"
#include "GameObject/Component/geometry/polygonCollider.h"
#include "GameObject/Component/geometry/position.h"
#include "GameObject/Component/geometry/velocity.h"
#include "GameObject\Component\gameplay\splash.h"
#include "Component\gameplay\beam.h"

GameObject * character()
{
    GameObject* g = new GameObject();

    g->addComponent<Sprite>()->texture = &TextureManager::spriteSheets[TextureManager::PRT];
    g->getComponent<Sprite>()->setWidthHeight(1, 2);
    g->getComponent<Sprite>()->setAnimationIndicies(0, 4);
    g->getComponent<Sprite>()->setRenderOffset(0, -24);
    g->addComponent<SpriteRenderer>()->setRenderLayer(1);
    g->addComponent<Movement>();

    g->addComponent<PolygonCollider>()->setStatic(false);
    g->getComponent<PolygonCollider>()->setPolygon(Rectangular(Point(3, 0), 26, 39.7));
    g->getComponent<PolygonCollider>()->addToMask(0);
    g->getComponent<Position>()->position = Point(50, 50);
    g->addComponent<Animator>()->addClip(AnimationClip{ "idle", 16, 21, 7 });
    g->getComponent<Animator>()->addClip(AnimationClip{ "running", 0, 4, 3 });
    g->getComponent<Animator>()->addClip(AnimationClip{ "falling", 32, 33, 7 });
    return g;
}

GameObject * muzzleFlash()
{
    GameObject* g = new GameObject();
    g->addComponent<Splash>();
    g->getComponent<Sprite>()->texture = &TextureManager::spriteSheets[TextureManager::PRT];
    return g;
}

GameObject * shrapnel1()
{
    GameObject* g = new GameObject();
    g->addComponent<Splash>()->setClip({"shrapnel", 227, 229, 3});
    g->getComponent<Sprite>()->texture = &TextureManager::spriteSheets[TextureManager::PRT];
    return g;
}

GameObject * laserBeam()
{
    GameObject* g = new GameObject();
    g->addComponent<Beam>();
    return g;
}
