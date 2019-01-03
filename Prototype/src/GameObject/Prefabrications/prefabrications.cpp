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
#include "GameObject\Component\gameplay\interactable\Door.h"
#include "System\sound\soundManager.h"

Character::Character() : Prefabrication("character")
{
}

GameObject * Character::instantiate(std::vector<std::string> parameters) const
{
    GameObject* g = new GameObject(name);

    g->addComponent<Sprite>()->texture = &TextureManager::spriteSheets[TextureManager::PRT];
    g->getComponent<Sprite>()->setWidthHeight(2, 4);
    g->getComponent<Sprite>()->setRenderOffset(0, -24);
    g->addComponent<SpriteRenderer>()->setRenderLayer(2);
    g->addComponent<Movement>();

    g->addComponent<PolygonCollider>()->setStatic(false);
    g->getComponent<PolygonCollider>()->setPolygon(Polyshape(26, 39.7, Point(3, 0)));
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

GameObject * MuzzleFlash::instantiate(std::vector<std::string> parameters) const
{
    GameObject* g = new GameObject(name);
    g->addComponent<Splash>();
    g->getComponent<Sprite>()->texture = &TextureManager::spriteSheets[TextureManager::PRT];
    g->getComponent<Sprite>()->setWidthHeight(2, 2); //uncomment if tile-size is set to 16x16
    return g;
}

Shrapnel::Shrapnel() : Prefabrication("shrapnel")
{
}

GameObject * Shrapnel::instantiate(std::vector<std::string> parameters) const
{
    GameObject* g = new GameObject(name);
    g->addComponent<Splash>()->setClip({ "shrapnel", 227, 229, 3 });
    g->getComponent<Sprite>()->texture = &TextureManager::spriteSheets[TextureManager::PRT];
    g->getComponent<Sprite>()->setWidthHeight(2, 2); //uncomment if tile-size is set to 16x16
    return g;
}

LaserBeam::LaserBeam() : Prefabrication("beam")
{
}

GameObject * LaserBeam::instantiate(std::vector<std::string> parameters) const
{
    GameObject* g = new GameObject(name);
    g->addComponent<Beam>();
    return g;
}

GlassContainer::GlassContainer() : Prefabrication("glassContainer")
{
}

GameObject * GlassContainer::instantiate(std::vector<std::string> parameters) const
{
    GameObject* g = new GameObject(name);
    g->addComponent<Container>();
    return g;
}

DoorPrefab::DoorPrefab() : Prefabrication("doorContainer")
{
}

GameObject * DoorPrefab::instantiate(std::vector<std::string> parameters) const
{
    GameObject* g = new GameObject(name);
    Door *d = g->addComponent<Door>();
    //Path
    d->setPath("Assets/Rooms/" + parameters[0]);
    //Destination
    int x = parameters[1].empty() ? INT_MIN : std::stoi(parameters[1]);
    int y = parameters[2].empty() ? INT_MIN : std::stoi(parameters[2]);
    d->setDestination(x, y);
    //Dimensions
    double w = Tile::TILE_SIZE * std::stoi(parameters[3]);
    double h = Tile::TILE_SIZE * std::stoi(parameters[4]);
    d->setPolygon(Polyshape(w, h));
    return g;
}
