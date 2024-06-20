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

class EThreeMap : public AbstractEffectPlatform {
   public:
    EThreeMap() = default;
    EThreeMap(sf::Vector2f position, const std::string &texture_path);
    EThreeMap(const EThreeMap &other) = default;
    EThreeMap(const JsonObject *conf);
    ~EThreeMap() = default;
    void applyEffect();
    bool hit(sf::Sprite *sprite) override;

    EThreeMap &operator=(const EThreeMap &other);
};
