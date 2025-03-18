/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** Warp_futur
*/

#include "Warp_futur.hpp"

Warp_futur::Warp_futur(std::string str, std::pair<int, int> pos, std::pair<int, int> size) : Warp(str, pos, size)
{
    data["texture"] = str;
    sf::Texture texture;
    texture.loadFromFile(str);
    data["sfTexture"] = texture;
    data["x"] = pos.first;
    data["y"] = pos.second;
    data["TextureSize"] = size;
    data["Timeline"] = GameMap::FUTUR;
}