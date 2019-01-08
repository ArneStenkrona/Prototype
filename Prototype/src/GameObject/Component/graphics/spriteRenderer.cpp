#include "Gameobject/gameObject.h"
#include "spriteRenderer.h"
#include "System\graphics\graphicsEngine.h"
#include <iostream>


SpriteRenderer::SpriteRenderer(GameObject *_object) : Renderer(_object)
{
    position = requireComponent<Position>();
    sprite = requireComponent<Sprite>();  
    rotation = (object->hasComponent<Rotation>()) ? object->getComponent<Rotation>() : rotation;
}

void SpriteRenderer::updateComponents()
{

    position = (object->hasComponent<Position>()) ? object->getComponent<Position>() : position;
    sprite = (object->hasComponent<Sprite>()) ? object->getComponent<Sprite>() : sprite;
    rotation = (object->hasComponent<Rotation>()) ? object->getComponent<Rotation>() : rotation;
}

void SpriteRenderer::render()
{
    //Check if camera is available
    if (cameraPosition != nullptr) {
        Point renderPosition = position->position - cameraPosition->position;
        if (rotation != nullptr)
            sprite->renderSprite((int)renderPosition.x, (int)renderPosition.y, rotation->rotation, (int)rotation->pivot.x, (int)rotation->pivot.y);
        else sprite->renderSprite((int)renderPosition.x, (int)renderPosition.y);
    }
    else {
        std::cout << "No camera has been set for rendering" << std::endl;
    }
}
