/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** Pillar
*/

#include "Pillar.hpp"
#include <HitboxModule.hpp>
#include <MovementModule.hpp>
#include "Game.h"
#include <Game.hpp>
#include "GameObject.hpp"

void pillar_action(GameObject *player, GameObject *pillar)
{
    sf::Texture texture;
    texture.loadFromFile("../assets/totem_pillar/pillar_finished.png");
    pillar->data["sfTexture"] = texture;
    pillar->data["texture"] = "../assets/totem_pillar/pillar_finished.png";
    (void) player;
}

Pillar::Pillar(std::string str, std::pair<int, int> pos, std::pair<int, int> size)
{
    addModule<InteractionModule>();
    addModule<DisplayModule>();
    static int i = -2;

    data["texture"] = str;
    sf::Texture texture;
    texture.loadFromFile(str);
    data["sfTexture"] = texture;
    data["x"] = pos.first;
    data["y"] = pos.second;
    data["TextureSize"] = size;
    data["actionEffect"] = &pillar_action;
    data["pillar"] = i;
    i++;
}
