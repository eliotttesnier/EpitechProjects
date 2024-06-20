/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** Wall
*/

#pragma once

#include "GameObject.hpp"

class Wall : public GameObject {
    public:
        Wall(std::string, std::pair<int, int>, std::pair<int, int>);
        ~Wall() = default;

        sf::Texture getTexture(void) {return std::any_cast<sf::Texture>(data["texture"]);}
        std::pair<int, int> getPos(void) {return std::pair<int, int>(std::any_cast<int>(data["x"]), std::any_cast<int>(data["y"]));}
        std::pair<int, int> getSize(void) {return std::any_cast<std::pair<int, int>>(data["TextureSize"]);}
    protected:
    private:
};
