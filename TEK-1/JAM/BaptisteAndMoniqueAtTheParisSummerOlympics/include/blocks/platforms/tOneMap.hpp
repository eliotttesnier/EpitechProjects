/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "blocks/platforms/AbstractPlatform.hpp"

class TOneMap : public AbstractPlatform {
public:
    TOneMap(sf::Vector2f position, const std::string &texture_path);
    TOneMap(const TOneMap &other) = default;
    TOneMap(const JsonObject *json);
    ~TOneMap() = default;

    // ---------- Methods ----------
    bool hit(sf::Sprite *sprite) override;

    // ---------- Operator Overloads ----------
    TOneMap &operator=(const TOneMap &other);
};
