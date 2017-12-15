#include "camera.h"
#include <iostream>
#include "System/graphics/global_graphical_variables.h"
#include "World/room.h"
#include "System/gameLogic.h"
#include "GameObject/Component/geometry/polygonCollider.h"

const Point Camera::screenOffset = Point(SCREEN_WIDTH / SCALE_X, SCREEN_HEIGHT / SCALE_Y) * 0.5;

Camera::Camera(GameObject * _object) : Component(_object)
{
    if (object->hasComponent<Position>()) {
        position = object->getComponent<Position>();
    }
    else {
        position = object->addComponent<Position>();
    }
}

void Camera::start()
{
}

void Camera::update()
{
    double posX;
    double posY;

    Point targetPos = targetPosition->position + targetBounds * 0.5;

    Room *room = getRoom();
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
    if (object->hasComponent<Position>()) {
        position = object->getComponent<Position>();
    }
    if (target != nullptr) {
        targetPosition = target->getComponent<Position>();
    }
}

void Camera::setTarget(GameObject *targetObject)
{
    target = targetObject;
    targetPosition = target->getComponent<Position>();
    targetBounds = Point(targetObject->getComponent<PolygonCollider>()->getWidth(), targetObject->getComponent<PolygonCollider>()->getHeight());
}

Position * Camera::getPosition()
{
    return position;
}
