/*
** EPITECH PROJECT, 2024
** OpenThisFuckingDoor
** File description:
** Player
*/

#include <HitboxModule.hpp>
#include <MovementModule.hpp>
#include "Player.hpp"
#include "Game.h"
#include <Game.hpp>
#include "GameObject.hpp"

Player::Player(std::string str, std::pair<int, int> pos, std::pair<int, int> size)
{
    enum Direction dir = RIGHT;
    addModule<PlayerModule>();
    data["texture"] = str;
    data["x"] = pos.first;
    data["y"] = pos.second;
    data["TextureSize"] = size;
    data["speed"] = int(7);
    data["direction"] = dir;
}

void Player::displayPlayer(void)
{
#define coef 4
    sf::Texture minimap; minimap.loadFromFile("assets/minimap.png");
    sf::Texture mapdot; mapdot.loadFromFile("assets/mapdot.png");
    sf::Sprite sprite; sprite.setTexture(minimap);
    sf::Sprite dot; dot.setTexture(mapdot);

    float x = (float)std::any_cast<int>(data["x"]);
    float y = (float)std::any_cast<int>(data["y"]);
    std::pair size = std::any_cast<std::pair<int, int>>(data["TextureSize"]);
    sf::View view((sf::FloatRect){x - (192 * coef / 2) + (size.first / 2), y - (108 * coef / 2) + (size.second / 2), 192 * coef, 108 * coef});
    float xv = view.getCenter().x + 225;
    float yv = (int)view.getCenter().y - 205;

    game.getWindow().setView(view);

    sprite.setPosition((sf::Vector2f){xv, yv});
    game.getWindow().draw(sprite);

    dot.setPosition((sf::Vector2f){xv + ((int)(x / 100) % 100 * (float)1.45), yv + ((int)(y  / 100) % 100 * (float)1.45)});
    game.getWindow().draw(dot);
}
