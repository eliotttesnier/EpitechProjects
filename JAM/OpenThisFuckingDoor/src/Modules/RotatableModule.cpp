/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** Rotatable
*/

#include <RotatableModule.hpp>
#include <MovementModule.hpp>

RotatableModule::RotatableModule(GameObject *gameObject)
{
    if (gameObject->hasModule<RotatableModule>())
        throw Error("GameObject already has a RotatableModule!");
    if (gameObject->data.find("direction") == gameObject->data.end())
        gameObject->data["direction"] = Direction(IDLE);
}
