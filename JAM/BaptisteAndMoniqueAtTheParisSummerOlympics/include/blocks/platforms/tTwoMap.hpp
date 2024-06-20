/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "blocks/platforms/AbstractPlatform.hpp"

class TTwoMap : public AbstractPlatform {
public:
    TTwoMap(sf::Vector2f position, const std::string &texture_path);
    TTwoMap(const TTwoMap &other) = default;
    TTwoMap(const JsonObject *json);
    ~TTwoMap() = default;

    // ---------- Methods ----------
    bool hit(sf::Sprite *sprite) override;

    // ---------- Operator Overloads ----------
    TTwoMap &operator=(const TTwoMap &other);
};
