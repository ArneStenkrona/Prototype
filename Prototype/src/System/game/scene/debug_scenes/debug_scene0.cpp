#include "debug_scene0.h"
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

    GameObject *character = new GameObject();

    character->addComponent<Sprite>()->texture = &TextureManager::spriteSheets[TextureManager::PRT];
    character->getComponent<Sprite>()->setWidthHeight(1,2);
    character->getComponent<Sprite>()->setAnimationIndicies(0,4);
    character->getComponent<Sprite>()->setRenderOffset(0,-24);
    character->addComponent<Renderer>()->setRenderLayer(1);
    character->addComponent<Movement>();

    character->addComponent<PolygonCollider>()->setStatic(false);
    character->getComponent<PolygonCollider>()->setPolygon(Rectangular(Point(3, 0), 26, 39.7));
    character->getComponent<Position>()->position = Point(50, 50);
    character->addComponent<Animator>()->addClip(AnimationClip{"idle", 16, 21, 7 });
    character->getComponent<Animator>()->addClip(AnimationClip{"running", 0, 4, 3 });
    character->getComponent<Animator>()->addClip(AnimationClip{"falling", 32, 33, 7 });
    //character->getComponent<Animator>()->addClip(AnimationClip{ "debug", 127, 127, 7 });

    GameObject *testRot = new GameObject();
    testRot->addComponent<Sprite>()->texture = &TextureManager::tileMap.texture;
    testRot->getComponent<Sprite>()->setTileIndex(4);
    testRot->addComponent<Renderer>();
    testRot->addComponent<Position>();
    testRot->getComponent<Position>()->position = Point(50,50);
    testRot->addComponent<Rotation>()->rotation = 45;

    GameObject *camera = new GameObject();
    camera->addComponent<Camera>()->setTarget(character);
    Renderer::setCamera(camera);
}

