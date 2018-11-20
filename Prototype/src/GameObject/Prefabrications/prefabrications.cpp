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
#include "GameObject\Component\gameplay\beam.h"
#include "GameObject\Component\gameplay\interactable\Container.h"
#include "System\sound\soundManager.h"

Character::Character() : Prefabrication("character")
{
}

GameObject * Character::instantiate() const
{
    GameObject* g = new GameObject(name);

    g->addComponent<Sprite>()->texture = &TextureManager::spriteSheets[TextureManager::PRT];
    g->getComponent<Sprite>()->setWidthHeight(1, 2);
    g->getComponent<Sprite>()->setRenderOffset(0, -24);
    g->addComponent<SpriteRenderer>()->setRenderLayer(2);
    g->addComponent<Movement>();

    g->addComponent<PolygonCollider>()->setStatic(false);
    g->getComponent<PolygonCollider>()->setPolygon(Rectangular(Point(3, 0), 26, 39.7));
    g->getComponent<PolygonCollider>()->addToMask(0);
    g->getComponent<Position>()->position = Point(50, 50);
    g->addComponent<Animator>()->addClip(AnimationClip{ "idle", 16, 21, 7 });
    g->getComponent<Animator>()->addClip(AnimationClip{ "running", 0, 4, 3, { {1, SoundManager::FOOTSTEP_SOUND} } });
    g->getComponent<Animator>()->addClip(AnimationClip{ "falling", 32, 33, 7 });
    return g;
}

MuzzleFlash::MuzzleFlash() : Prefabrication("flash")
{
}

GameObject * MuzzleFlash::instantiate() const
{
    GameObject* g = new GameObject(name);
    g->addComponent<Splash>();
    g->getComponent<Sprite>()->texture = &TextureManager::spriteSheets[TextureManager::PRT];
    //sprite->setWidthHeight(2, 2); //uncomment if tile-size is set to 16x16
    return g;
}

Shrapnel::Shrapnel() : Prefabrication("shrapnel")
{
}

GameObject * Shrapnel::instantiate() const
{
    GameObject* g = new GameObject(name);
    g->addComponent<Splash>()->setClip({ "shrapnel", 227, 229, 3 });
    g->getComponent<Sprite>()->texture = &TextureManager::spriteSheets[TextureManager::PRT];
    //sprite->setWidthHeight(2, 2); //uncomment if tile-size is set to 16x16
    return g;
}

LaserBeam::LaserBeam() : Prefabrication("beam")
{
}

GameObject * LaserBeam::instantiate() const
{
    GameObject* g = new GameObject(name);
    g->addComponent<Beam>();
    return g;
}

GlassContainer::GlassContainer() : Prefabrication("glassContainer")
{
}

GameObject * GlassContainer::instantiate() const
{
    GameObject* g = new GameObject(name);
    g->addComponent<Container>();
    return g;
}
