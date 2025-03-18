/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** Totem
*/

#include <HitboxModule.hpp>
#include <MovementModule.hpp>
#include "Totem.hpp"
#include "Game.h"
#include <Game.hpp>
#include "GameObject.hpp"

void totem_action(GameObject *player, GameObject *totem)
{
    player->data["hasTotem"] = true;
    totem->data["x"] = -1000;
    totem->data["y"] = -1000;
}

Totem::Totem(std::string str, std::pair<int, int> pos, std::pair<int, int> size)
{
    addModule<InteractionModule>();
    addModule<DisplayModule>();
    sf::Texture tex;
    tex.loadFromFile(str);
    data["texture"] = str;
    sf::Texture text;
    text.loadFromFile("./assets/totem.png");
    data["sfTexture"] = text;
    data["x"] = pos.first;
    data["y"] = pos.second;
    data["TextureSize"] = size;
    data["actionEffect"] = &totem_action;
    data["isTotem"] = true;
    data["totem"] = 1;
}
