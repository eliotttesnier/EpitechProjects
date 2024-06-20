/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** PositionModule
*/

#include "PositionModule.hpp"
#include <GameObject.hpp>

PositionModule::PositionModule(GameObject *gameObject)
{
    if (gameObject->hasModule<PositionModule>())
        throw Error("GameObject already has a PositionModule!");
    if (gameObject->data.find("x") == gameObject->data.end())
        gameObject->data["x"] = int(0);
    if (gameObject->data.find("y") == gameObject->data.end())
        gameObject->data["y"] = int(0);
}
