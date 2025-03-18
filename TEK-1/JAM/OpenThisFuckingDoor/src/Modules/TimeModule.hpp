/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** TimeModule
*/

#pragma once

#include <GameObject.hpp>

class TimeModule : public Module {
    public:
        TimeModule(GameObject *gameObject);
        ~TimeModule() = default;

        void update(GameObject *gameObject, std::vector<GameObject*> gameObjects) override;
    protected:
    private:
};
