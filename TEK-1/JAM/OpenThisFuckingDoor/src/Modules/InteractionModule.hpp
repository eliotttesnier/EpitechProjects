/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "../Game/GameObject.hpp"
#include "functional"

class InteractionModule : public Module {
public:
    InteractionModule(GameObject *gameObject);
    ~InteractionModule() = default;

    // Setters
    void setRange(float range) {_range = range;}
    void setActionEffect(GameObject *gameObject, std::function<void(GameObject *, GameObject *)> actionEffect);

    // Getters
    float getRange() const {return _range;}

    void update(GameObject *gameObject, std::vector<GameObject*> gameObjects) override;
    bool infrontof(GameObject *gameobject, GameObject *otherobject);
private:
    double _range;
};
