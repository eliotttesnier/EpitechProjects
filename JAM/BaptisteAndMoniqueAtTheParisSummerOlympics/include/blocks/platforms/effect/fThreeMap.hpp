/*
** EPITECH PROJECT, 2024
** BaptisteAndMoniqueAtTheParisSummerOlympics
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "blocks/platforms/effect/AbstractEffectPlatform.hpp"
#include "Game.hpp"

class FThreeMap : public AbstractEffectPlatform {
   public:
    FThreeMap() = default;
    FThreeMap(sf::Vector2f position, const std::string &texture_path);
    FThreeMap(const FThreeMap &other) = default;
    FThreeMap(const JsonObject *conf);
    ~FThreeMap() = default;
    void applyEffect();
    bool hit(sf::Sprite *sprite) override;

    FThreeMap &operator=(const FThreeMap &other);
};
