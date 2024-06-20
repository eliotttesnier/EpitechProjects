/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include <string>
#include <vector>

class GameObject;

class Module {
public:
    virtual void update(GameObject *gameObject, std::vector<GameObject*> gameObjects) = 0;
    virtual ~Module() = default;
    class Error : public std::exception {
        public:
            Error (const std::string &msg)
            {
                _msg = msg;
            }

            const char *what() const noexcept override
            {
                return _msg.c_str();
            }
        private:
            std::string _msg;
    };
};

