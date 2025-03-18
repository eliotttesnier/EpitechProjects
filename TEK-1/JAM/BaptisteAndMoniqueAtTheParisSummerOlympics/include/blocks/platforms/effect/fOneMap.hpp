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

class FOneMap : public AbstractEffectPlatform {
   public:
    FOneMap() = default;
    FOneMap(sf::Vector2f position, const std::string &texture_path);
    FOneMap(const FOneMap &other) = default;
    FOneMap(const JsonObject *conf);
    ~FOneMap() = default;
    void applyEffect();
    bool hit(sf::Sprite *sprite) override;

    FOneMap &operator=(const FOneMap &other);
};
