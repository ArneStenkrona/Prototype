#include "renderer.h"
#include "System\graphics\global_graphical_variables.h"
#include "Gameobject/gameObject.h"
#include <iostream>

GameObject* Renderer::mainCamera = nullptr;
Position* Renderer::cameraPosition = nullptr;

Renderer::Renderer(GameObject *_object) : renderer(ACTIVE_RENDERER), Component(_object), tileQuad(NULL)
{

    //Required
    if (object->hasComponent<Position>()) {
        position = object->getComponent<Position>();
    }
    else {
        position = object->addComponent<Position>();
    }
    if (object->hasComponent<Sprite>()) {
        sprite = object->getComponent<Sprite>();
    }
    else {
        sprite = object->addComponent<Sprite>();
    }
}

void Renderer::updateComponents()
{
    if (object->hasComponent<Position>()) {
        position = object->getComponent<Position>();
    }

    if (object->hasComponent<Sprite>()) {
        sprite = object->getComponent<Sprite>();
    }

    if (mainCamera != nullptr) {
        cameraPosition = mainCamera->getComponent<Position>();
    }
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

void Renderer::setTileQuad(SDL_Rect * _quad)
{
    tileQuad = _quad;
}

void Renderer::start() {


}

void Renderer::update() {

    //Cehck if camera is available
    if (cameraPosition != nullptr) {

        Point pos;
        Point cameraPos = cameraPosition->position;
        pos = position->position - cameraPos;
        if (sprite != nullptr) {
            if (tileQuad == NULL) {
                sprite->texture->render(pos.x, pos.y);
            }
            else {
                sprite->texture->renderTile(pos.x, pos.y, tileQuad);
            }
        }
    }
    else {
        std::cout << "No camera has been set for rendering" << std::endl;
    }
}
