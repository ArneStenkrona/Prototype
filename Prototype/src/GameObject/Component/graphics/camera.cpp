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
    unsigned int left, right, top, bottom;
    room->getPadding(left, right, top, bottom);

    //Prevent camera from going to far to the right (positive dx)
    if (targetPos.x + screenOffset.x > roomPos.x + roomDimensions.x - right * Tile::TILE_SIZE) {
        posX = roomDimensions.x + roomPos.x - 2 * screenOffset.x - right * Tile::TILE_SIZE;
    }
    //Prevent camera from going to far to the left (negative dx)
    else if (targetPos.x - screenOffset.x < roomPos.x + left * Tile::TILE_SIZE) {
        posX = roomPos.x + left * Tile::TILE_SIZE;
    }
    else {
        posX = targetPos.x - screenOffset.x;
    }
    //Prevent camera from going to far down (positive dy)
    if (targetPos.y + screenOffset.y > roomPos.y + roomDimensions.y - bottom * Tile::TILE_SIZE) {

        posY = roomDimensions.y + roomPos.y - 2 * screenOffset.y - bottom * Tile::TILE_SIZE;
    }
    //Prevent camera from going to far up (negative dy)
    else if (targetPos.y - screenOffset.y < roomPos.y + top * Tile::TILE_SIZE) {
        posY = roomPos.y + top * Tile::TILE_SIZE;
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