/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "../Modules/Module.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <any>

class GameObject {
public:
    GameObject() = default;
    ~GameObject() {
        for (auto module : modules) {
            delete module.second;
        }
    }

    // Add a module to the GameObject
    template <typename T>
    void addModule() {
        modules[typeid(T).name()] = new T(this);
    }

    // Check if the GameObject has a specific module
    template <typename T>
    bool hasModule() const {
        return modules.find(typeid(T).name()) != modules.end();
    }

    // Update all modules
    void update(std::vector<GameObject*> gameObjects)
    {
        for (auto module : modules) {
            for (auto gameObject : gameObjects) {
                module.second->update(gameObject, gameObjects);
            }
        }
    }

    std::unordered_map<std::string, std::any> data;
    std::unordered_map<std::string, Module*> modules;
};
