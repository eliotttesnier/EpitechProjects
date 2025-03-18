/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "../Game/GameObject.hpp"

class CollisionModule : public Module {
public:
    CollisionModule(GameObject *gameObject);
    ~CollisionModule() = default;

    void update(GameObject *gameObject, std::vector<GameObject*> gameObjects) override {(void) gameObject, (void) gameObjects;};
private:
};
