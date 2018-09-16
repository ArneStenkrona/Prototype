#include "Gameobject/gameObject.h"
#include "renderer.h"
#include "System\graphics\graphicsEngine.h"
#include "camera.h"
#include <iostream>

GameObject* Renderer::mainCamera = nullptr;
Position* Renderer::cameraPosition = nullptr;

Renderer::Renderer(GameObject * _object) : Component(_object), renderLayer(0)
{
}

Renderer::~Renderer()
{
    GraphicsEngine::removeFromRenderQueue(this, renderLayer);
}

void Renderer::onActivate()
{
    GraphicsEngine::addToRenderQueue(this, renderLayer);
}

void Renderer::onDeactivate()
{
    GraphicsEngine::removeFromRenderQueue(this, renderLayer);
}

void Renderer::start()
{
}

void Renderer::update()
{
}

void Renderer::setRenderLayer(unsigned int layer)
{
    GraphicsEngine::removeFromRenderQueue(this, renderLayer);
    renderLayer = layer;
    GraphicsEngine::addToRenderQueue(this, layer);
}

void Renderer::setCamera(GameObject * _camera)
{
    if (_camera->hasComponent<Camera>()) {
        mainCamera = _camera;
        cameraPosition = mainCamera->getComponent<Position>();
    }
    else {
        std::cout << "Renderer::setCamera() failure: GameObject has no Camera component." << std::endl;
    }
}

void Renderer::render()
{
}
