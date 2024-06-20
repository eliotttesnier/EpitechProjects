/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** Player
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <unordered_map>
#include <GameObject.hpp>
#include <PlayerModule.hpp>

class Player : public GameObject {
    public:
        Player(std::string str, std::pair<int, int> pos, std::pair<int, int> size);
        ~Player() = default;

        // Getters
        sf::Texture getTexture(void) {return std::any_cast<sf::Texture>(data["texture"]);}
        std::pair<int, int> getPos(void) {return std::pair<int, int>(std::any_cast<int>(data["x"]), std::any_cast<int>(data["y"]));}
        std::pair<int, int> getSize(void) {return std::any_cast<std::pair<int, int>>(data["TextureSize"]);}

        // Display

        void displayPlayer(void);
    protected:
    private:
};
