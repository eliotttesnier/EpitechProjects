/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** Warp
*/

#include "Warp.hpp"

void event_action(GameObject *player, GameObject *warp)
{
    (void) player;
    game.setTimeLine(std::any_cast<GameMap::TimeLine>(warp->data["Timeline"]));
}

Warp::Warp(std::string str, std::pair<int, int> pos, std::pair<int, int> size)
{
    addModule<DisplayModule>();
    addModule<EventModule>();

    sf::Texture texture;
    texture.loadFromFile(str);
    data["sfTexture"] = texture;
    data["x"] = pos.first;
    data["y"] = pos.second;
    data["TextureSize"] = size;
    data["eventEffect"] = &event_action;
}