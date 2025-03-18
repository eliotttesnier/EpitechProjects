/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** No file there , just an epitech header example .
*/

#include "PlayerModule.hpp"
#include "HitboxModule.hpp"
#include "CollisionModule.hpp"
#include "InteractionModule.hpp"

void setActionEffect(GameObject *gameObject, std::function<void(GameObject *, GameObject *)> actionEffect)
{
    gameObject->data["actionEffect"] = actionEffect;
}

InteractionModule::InteractionModule(GameObject *gameObject)
{
    if (gameObject->hasModule<InteractionModule>())
        throw Error("Already has Interaction module.");
    if (!gameObject->hasModule<CollisionModule>())
        gameObject->addModule<CollisionModule>();
    if (gameObject->data.find("actionEffect") == gameObject->data.end())
        gameObject->data["actionEffect"] = NULL;
}

bool InteractionModule::infrontof(GameObject *obj1, GameObject *obj2)
{
    if (HitboxModule::calculateDistance(obj1, obj2) < _range)
        return (true);
    return (false);
}

void InteractionModule::update(GameObject *gameObject, std::vector<GameObject*> allObjects)
{
    for (auto& otherObject : allObjects) {
        if (otherObject->hasModule<PlayerModule>() && InteractionModule::infrontof(gameObject, otherObject) && std::any_cast<bool>(otherObject->data["interacting"])) {
            std::any_cast<std::function<void(GameObject *, GameObject *)>>(gameObject->data["eventEffect"])(otherObject, gameObject);
        }
    }
}
