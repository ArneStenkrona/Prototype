#include "renderer.h"
#include "System\graphics\global_graphical_variables.h"
#include "Gameobject/gameObject.h"
#include <iostream>

GameObject* Renderer::mainCamera = nullptr;
Position* Renderer::cameraPosition = nullptr;

Renderer::Renderer(GameObject *_object) : renderer(ACTIVE_RENDERER), Component(_object)//, tileIndex(-1)
{
    position = requireComponent<Position>();
    sprite = requireComponent<Sprite>();
}

void Renderer::updateComponents()
{

    position = (object->hasComponent<Position>()) ? object->getComponent<Position>() : position;
    sprite = (object->hasComponent<Sprite>()) ? object->getComponent<Sprite>() : sprite;

    /*if (mainCamera != nullptr) {
        cameraPosition = mainCamera->getComponent<Position>();
    }*/
}

void Renderer::setCamera(GameObject *_camera)
{
    if (_camera->hasComponent<Camera>()) {
        mainCamera = _camera;
        cameraPosition = mainCamera->getComponent<Position>();
    }
    else {
        std::cout << "Renderer::setCamera() failure: GameObject has no Camera component." << std::endl;
    }
}

Point Renderer::getCameraPosition()
{
    return mainCamera->getComponent<Position>()->position;
}

void Renderer::setTileIndex(int index)
{
    //tileIndex = index;
}

void Renderer::start() {


}

void Renderer::update() {

    //Cehck if camera is available
    if (cameraPosition != nullptr) {

        Point pos;
        Point cameraPos = cameraPosition->position;
        pos = position->position - cameraPos;
        sprite->renderSprite(pos.x, pos.y);
        /*
        int tileIndex = sprite->getTileIndex();
        if (tileIndex == -1) {
            sprite->texture->render((int)(pos.x + 0.5), (int)(pos.y + 0.5));
        }
        else {
            sprite->texture->renderTile((int)(pos.x + 0.5), (int)(pos.y + 0.5), tileIndex);
        }*/
      
    }
    else {
        std::cout << "No camera has been set for rendering" << std::endl;
    }
}
