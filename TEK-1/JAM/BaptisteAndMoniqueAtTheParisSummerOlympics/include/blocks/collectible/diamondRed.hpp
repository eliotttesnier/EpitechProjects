/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "blocks/collectible/AbstractCollectible.hpp"

class DiamondRed : public AbstractCollectible {
   public:
    DiamondRed();
    DiamondRed(sf::Vector2f position, const std::string &texture_path);
    DiamondRed(const JsonObject *object);
    ~DiamondRed() override = default;
};
