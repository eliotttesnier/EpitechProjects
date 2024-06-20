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

class PThreeMap : public AbstractEffectPlatform {
   public:
    PThreeMap() = default;
    PThreeMap(sf::Vector2f position, const std::string &texture_path);
    PThreeMap(const PThreeMap &other) = default;
    PThreeMap(const JsonObject *conf);
    ~PThreeMap() = default;
    void applyEffect();
    bool hit(sf::Sprite *sprite) override;

    PThreeMap &operator=(const PThreeMap &other);
};
