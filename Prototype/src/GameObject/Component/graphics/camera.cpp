#include "camera.h"
#include <iostream>
#include "System/graphics/graphicsEngine.h"
#include "World/room.h"
#include "System/game/gameLogic.h"
#include "GameObject/Component/geometry/polygonCollider.h"

const Point Camera::screenOffset = Point(GraphicsEngine::SCREEN_WIDTH / GraphicsEngine::SCALE_X, GraphicsEngine::SCREEN_HEIGHT / GraphicsEngine::SCALE_Y) * 0.5;

Camera::Camera(GameObject * _object) : Component(_object)
{
    position = requireComponent<Position>();
}

void Camera::start()
{
}

void Camera::lateUpdate()
{
    double posX;
    double posY;

    Point targetPos = targetPosition->position + targetBounds * 0.5;

    Room *room = GameLogic::getRoom();
    Point roomPos = room->getPosition();
    Point roomDimensions = room->getDimensions();

    if (targetPos.x + screenOffset.x > roomDimensions.x + roomPos.x) {

        posX = roomDimensions.x + roomPos.x - 2 * screenOffset.x;
    }
    else if (targetPos.x - screenOffset.x < roomPos.x) {
        posX = roomPos.x;
    }
    else {
        posX = targetPos.x - screenOffset.x;
    }

    if (targetPos.y + screenOffset.y > roomDimensions.y + roomPos.y) {

        posY = roomDimensions.y + roomPos.y - 2 * screenOffset.y;
    }
    else if (targetPos.y - screenOffset.y < roomPos.y) {
        posY = roomPos.y;
    }
    else {
        posY = targetPos.y - screenOffset.y;
    }


    if (targetPosition != nullptr) {
        position->position = Point(posX, posY);
    }
}

void Camera::updateComponents()
{
    position = (object->hasComponent<Position>()) ? object->getComponent<Position>() : position;

    /*if (target != nullptr) {
        targetPosition = target->getComponent<Position>();
    }*/
}

void Camera::setTarget(GameObject *targetObject)
{
    target = targetObject;
    targetPosition = target->getComponent<Position>();
    targetBounds = Point(targetObject->getComponent<PolygonCollider>()->getWidth(), targetObject->getComponent<PolygonCollider>()->getHeight());
}