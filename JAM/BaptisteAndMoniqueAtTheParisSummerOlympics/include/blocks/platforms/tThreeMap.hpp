/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "blocks/platforms/AbstractPlatform.hpp"

class TThreeMap : public AbstractPlatform {
public:
    TThreeMap(sf::Vector2f position, const std::string &texture_path);
    TThreeMap(const TThreeMap &other) = default;
    TThreeMap(const JsonObject *json);
    ~TThreeMap() = default;

    // ---------- Methods ----------
    bool hit(sf::Sprite *sprite) override;

    // ---------- Operator Overloads ----------
    TThreeMap &operator=(const TThreeMap &other);
};
