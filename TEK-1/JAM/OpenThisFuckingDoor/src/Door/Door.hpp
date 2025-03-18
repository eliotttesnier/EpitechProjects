/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** Door
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <unordered_map>
#include <GameObject.hpp>
#include <CollisionModule.hpp>

class Door : public GameObject {
    public:
        Door(std::string str, std::pair<int, int> pos, std::pair<int, int> size);
        ~Door() = default;

        // Getters
        sf::Texture getTexture(void) {return std::any_cast<sf::Texture>(data["texture"]);}
        std::pair<int, int> getPos(void) {return std::pair<int, int>(std::any_cast<int>(data["x"]), std::any_cast<int>(data["y"]));}
        std::pair<int, int> getSize(void) {return std::any_cast<std::pair<int, int>>(data["TextureSize"]);}

    protected:
    private:
};
