/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "../Game/GameObject.hpp"

enum Direction {
    IDLE = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class MovementModule : public Module {
public:
    MovementModule(GameObject *gameObject);
    ~MovementModule() = default;

    void setDirection(GameObject *gameObject, Direction direction);
    void setSpeed(GameObject *gameObject, int speed);

    void update(GameObject *gameObject, std::vector<GameObject*> gameObjects) override;

};
