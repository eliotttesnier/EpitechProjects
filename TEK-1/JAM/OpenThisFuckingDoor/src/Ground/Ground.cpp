/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** Ground
*/

#include "Ground.hpp"
#include "PositionModule.hpp"
#include "DisplayModule.hpp"

Ground::Ground(std::string str, std::pair<int, int> pos, std::pair<int, int> size)
{
    addModule<PositionModule>();
    addModule<DisplayModule>();
    sf::Texture texture;
    texture.loadFromFile(str);
    data["sfTexture"] = texture;
    data["x"] = pos.first;
    data["y"] = pos.second;
    data["TextureSize"] = size;
}
