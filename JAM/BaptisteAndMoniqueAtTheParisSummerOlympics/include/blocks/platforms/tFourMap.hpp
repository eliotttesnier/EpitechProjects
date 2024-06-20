/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "blocks/platforms/AbstractPlatform.hpp"

class TFourMap : public AbstractPlatform {
public:
    TFourMap(sf::Vector2f position, const std::string &texture_path);
    TFourMap(const TFourMap &other) = default;
    TFourMap(const JsonObject *json);
    ~TFourMap() = default;

    // ---------- Methods ----------
    bool hit(sf::Sprite *sprite) override;

    // ---------- Operator Overloads ----------
    TFourMap &operator=(const TFourMap &other);
};
