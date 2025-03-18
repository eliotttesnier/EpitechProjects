/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** No file there , just an epitech header example .
*/

#include "MovementModule.hpp"
#include "PositionModule.hpp"
#include <cmath>

MovementModule::MovementModule(GameObject *gameObject)
{
    if (gameObject->hasModule<MovementModule>())
        throw Error("GameObject already has a MovementModule!");
    if (!gameObject->hasModule<PositionModule>())
        gameObject->addModule<PositionModule>();
    if (gameObject->data.find("direction") == gameObject->data.end())
        gameObject->data["direction"] = Direction(IDLE);
    if (gameObject->data.find("speed") == gameObject->data.end())
        gameObject->data["speed"] = int(0);
}

void MovementModule::setDirection(GameObject *gameObject, Direction direction)
{
    gameObject->data["direction"] = direction;
}

void MovementModule::setSpeed(GameObject *gameObject, int speed)
{
    gameObject->data["speed"] = speed;
}

void MovementModule::update(GameObject *gameObject, std::vector<GameObject*> gameObjects)
{
    (void) gameObjects;

    if (std::any_cast<Direction>(gameObject->data["direction"]) == IDLE)
        return;
    if (std::any_cast<Direction>(gameObject->data["direction"]) == UP)
        gameObject->data["y"] = std::any_cast<int>(gameObject->data["y"]) - std::any_cast<int>(gameObject->data["speed"]);
    if (std::any_cast<Direction>(gameObject->data["direction"]) == DOWN)
        gameObject->data["y"] = std::any_cast<int>(gameObject->data["y"]) + std::any_cast<int>(gameObject->data["speed"]);
    if (std::any_cast<Direction>(gameObject->data["direction"]) == LEFT)
        gameObject->data["x"] = std::any_cast<int>(gameObject->data["x"]) - std::any_cast<int>(gameObject->data["speed"]);
    if (std::any_cast<Direction>(gameObject->data["direction"]) == RIGHT)
        gameObject->data["x"] = std::any_cast<int>(gameObject->data["x"]) + std::any_cast<int>(gameObject->data["speed"]);
}
