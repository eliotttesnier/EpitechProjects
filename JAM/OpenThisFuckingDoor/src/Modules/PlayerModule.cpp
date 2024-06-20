/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** No file there , just an epitech header example .
*/

#include "PlayerModule.hpp"

PlayerModule::PlayerModule(GameObject *gameObject)
{
    if (gameObject->hasModule<PlayerModule>())
        throw Error("GameObject already has a PlayerModule!");
    if (!gameObject->hasModule<HitboxModule>())
        gameObject->addModule<HitboxModule>();
    if (!gameObject->hasModule<CollisionModule>())
        gameObject->addModule<CollisionModule>();
    if (!gameObject->hasModule<DisplayModule>())
        gameObject->addModule<DisplayModule>();
    if (!gameObject->hasModule<MovementModule>())
        gameObject->addModule<MovementModule>();
    if (!gameObject->hasModule<PositionModule>())
        gameObject->addModule<PositionModule>();
    if (!gameObject->hasModule<RotatableModule>())
        gameObject->addModule<RotatableModule>();
    if (!gameObject->hasModule<TimeModule>())
        gameObject->addModule<TimeModule>();
    if (gameObject->data.find("interacting") == gameObject->data.end())
        gameObject->data["interacting"] = (bool)false;
    if (gameObject->data.find("hasTotem") == gameObject->data.end())
        gameObject->data["hasTotem"] = (bool)false;
}
