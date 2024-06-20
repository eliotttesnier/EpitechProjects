/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "blocks/platforms/moving/AbstractMovingPlatform.hpp"
#include "blocks/movingColor.hpp"

class POneBlock : public AbstractMovingPlatform {
protected:
    MovingColor _color;
public:
    POneBlock() = default;
    POneBlock(sf::Vector2f start_pos, sf::Vector2f end_pos, float speed, const std::string &texture_path, MovingColor color);
    POneBlock(const JsonObject *conf);
    ~POneBlock() override = default;

    bool hit(sf::Sprite *sprite) override;
};
