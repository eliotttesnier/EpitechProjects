/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** Door
*/

#include <HitboxModule.hpp>
#include "Door.hpp"
#include "Game.h"
#include <Game.hpp>
#include "GameObject.hpp"

Door::Door(std::string str, std::pair<int, int> pos, std::pair<int, int> size)
{
    addModule<DisplayModule>();
    addModule<CollisionModule>();
    (void)size;
    data["texture"] = str;
    sf::Texture text;
    text.loadFromFile("./assets/Door/door_1.png");
    data["sfTexture"] = text;
    data["x"] = pos.first - 22;
    data["y"] = pos.second + 400;
    data["TextureSize"] = std::pair<int, int>(126, 131);
}
