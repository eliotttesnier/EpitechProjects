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

class DOneBlock : public AbstractMovingPlatform {
protected:
    MovingColor _color;
public:
    DOneBlock() = default;
    DOneBlock(sf::Vector2f start_pos, sf::Vector2f end_pos, float speed, const std::string &texture_path, MovingColor color);
    DOneBlock(const JsonObject *conf);
    ~DOneBlock() override = default;

    bool hit(sf::Sprite *sprite) override;
};
