#include "renderer.h"
#include "System\graphics\graphicsEngine.h"
#include "Gameobject/gameObject.h"
#include <iostream>
#include "System\graphics\graphicsEngine.h"

GameObject* Renderer::mainCamera = nullptr;
Position* Renderer::cameraPosition = nullptr;

Renderer::Renderer(GameObject *_object) : renderer(GraphicsEngine::getActiveRenderer()), Component(_object), renderLayer(0)
{
    position = requireComponent<Position>();
    sprite = requireComponent<Sprite>();  
    rotation = (object->hasComponent<Rotation>()) ? object->getComponent<Rotation>() : rotation;
}

Renderer::~Renderer()
{
    GraphicsEngine::removeFromRenderQueue(this, renderLayer);
}

void Renderer::updateComponents()
{

    position = (object->hasComponent<Position>()) ? object->getComponent<Position>() : position;
    sprite = (object->hasComponent<Sprite>()) ? object->getComponent<Sprite>() : sprite;
    rotation = (object->hasComponent<Rotation>()) ? object->getComponent<Rotation>() : rotation;

    /*if (mainCamera != nullptr) {
        cameraPosition = mainCamera->getComponent<Position>();
    }*/
}

void Renderer::setRenderLayer(int layer)
{
    if (layer < 0) throw invalid_argument("Expected positive index");
    GraphicsEngine::removeFromRenderQueue(this, renderLayer);
    renderLayer = layer;
    GraphicsEngine::addToRenderQueue(this, layer);
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

void Renderer::render()
{
    //Check if camera is available
    if (cameraPosition != nullptr) {
        Point renderPosition;
        Point cameraPos = cameraPosition->position;
        renderPosition = position->position - cameraPos;
        if (rotation)
            sprite->renderSprite(renderPosition.x, renderPosition.y, rotation->rotation);
        else sprite->renderSprite(renderPosition.x, renderPosition.y);
    }
    else {
        std::cout << "No camera has been set for rendering" << std::endl;
    }
}

void Renderer::start() {
    GraphicsEngine::addToRenderQueue(this, renderLayer);
}



void Renderer::update() {
}
