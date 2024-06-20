/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "blocks/platforms/AbstractPlatform.hpp"

class BMap : public AbstractPlatform {
public:
    BMap(sf::Vector2f position, const std::string &texture_path);
    BMap(const BMap &other) = default;
    BMap(const JsonObject *json);
    ~BMap() = default;

    // ---------- Methods ----------
    bool hit(sf::Sprite *sprite) override;

    // ---------- Operator Overloads ----------
    BMap &operator=(const BMap &other);
};
