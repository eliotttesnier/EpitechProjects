/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** RotatableModule
*/

#pragma once

#include <GameObject.hpp>

class RotatableModule : public Module {
    public:
        RotatableModule(GameObject *gameObject);
        ~RotatableModule() = default;

        void update(GameObject *gameObject, std::vector<GameObject*> gameObjects) override {(void) gameObject, (void) gameObjects;}
    protected:
    private:
};
