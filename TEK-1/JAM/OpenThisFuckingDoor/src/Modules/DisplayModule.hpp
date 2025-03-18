/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** DisplayModule
*/

#pragma once

#include <GameObject.hpp>

class DisplayModule : public Module {
    public:
        DisplayModule(GameObject *gameObject);
        ~DisplayModule() = default;

        void update(GameObject *gameObject, std::vector<GameObject*> gameObjects) override;
};
