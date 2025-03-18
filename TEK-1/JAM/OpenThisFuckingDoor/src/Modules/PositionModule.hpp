/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** PositionModule
*/

#pragma once

#include <Module.hpp>

class PositionModule : public Module {
    public:
        PositionModule(GameObject *gameObject) ;
        ~PositionModule() = default;

        void update(GameObject *gameObject, std::vector<GameObject*> gameObjects) override {(void) gameObject, (void) gameObjects;};
    protected:
    private:
};
