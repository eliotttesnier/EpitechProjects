/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** Ground
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <GameObject.hpp>

class Ground : public GameObject {
    public:
        Ground(std::string, std::pair<int, int>, std::pair<int, int>);
        ~Ground() = default;

        // Getters
        sf::Texture getTexture(void) {return std::any_cast<sf::Texture>(data["texture"]);}
        std::pair<int, int> getPos(void) {return std::pair<int, int>(std::any_cast<int>(data["x"]), std::any_cast<int>(data["y"]));}
        std::pair<int, int> getSize(void) {return std::any_cast<std::pair<int, int>>(data["TextureSize"]);}

    protected:
    private:
};
